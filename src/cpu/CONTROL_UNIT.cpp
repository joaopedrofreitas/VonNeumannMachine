#include "CONTROL_UNIT.h"
#include <bitset>

// TODO 
// - Implement print, li, la, lw, sw, j

vector<queue<int>> WAITING_QUEUE2(3); //LOAD | PRINT | STORE
vector<int> PERMISSIONS2 = {0,0,0}; //LOAD | PRINT | STORE

uint32_t ConvertToDecimalValue(uint32_t value){
    string bin_str = to_string(value);
        uint32_t decimal_value = 0;       
        int len = bin_str.length();
        for (int i = 0; i < len; ++i) {
        if (bin_str[i] == '1') {
            decimal_value += std::pow(2, len - 1 - i);
            }
        }
    return decimal_value;
}

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers, bool &endProgram, MainMemory &ram, PCB &pcb, int id){
    const uint32_t instruction = registers.ir.read();
    if(PERMISSIONS2[0] == 1)
    {
        WAITING_QUEUE2[0].push(id);
        while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
        if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
    }
    PERMISSIONS2[0] = 1;
    //cout<<"REGISTER MAR: "<<registers.mar.read()<<endl;
    registers.ir.write(ram.ReadMem(registers.mar.read()));
    PERMISSIONS2[0] = 0;
    if(instruction == 0b11111100000000000000000000000000)
    {
        endProgram = true;
        return;
    }
    //registers.pc.write(pcb.program_counter);
    registers.mar.write(registers.pc.value);
    if(PERMISSIONS2[0] == 1)
    {
        WAITING_QUEUE2[0].push(id);
        while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
        if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
    }
    PERMISSIONS2[0] = 1;
    registers.ir.write(ram.ReadMem(registers.mar.read()));
    PERMISSIONS2[0] = 0;
    registers.pc.write(registers.pc.value += 1);//incrementando o pc
    pcb.program_counter += 1; 
}

void Control_Unit::Decode(REGISTER_BANK &registers, Instruction_Data &data){

    const uint32_t instruction = registers.ir.read();
    data.op = Identificacao_instrucao(instruction,registers);

    if(data.op == "ADD" || data.op == "SUB" || data.op == "MULT" || data.op == "DIV"){
        // se entrar aqui é porque tem de carregar registradores, que estão especificados na instrução
        data.source_register = Get_source_Register(instruction);
        data.target_register = Get_target_Register(instruction);
        data.destination_register = Get_destination_Register(instruction);

    }else if(data.op == "LI" || data.op == "LW" || data.op == "LA" || data.op == "SW")
    {
        data.target_register = Get_target_Register(instruction);
        data.addressRAMResult = Get_immediate(instruction);

    }else if(data.op == "BLT" || data.op == "BGT" || data.op == "BGTI" || data.op == "BLTI"){
        data.source_register = Get_source_Register(instruction);
        data.target_register = Get_target_Register(instruction);
        data.addressRAMResult = Get_immediate(instruction);   
    }
    else if(data.op == "J"){
        data.addressRAMResult = Get_immediate(instruction);
    }
    else if(data.op == "PRINT"){
        string instrucao = to_string(instruction);
        if(Get_immediate(instruction) == "0000000000000000"){   //se for zero, então é um registrador
            data.target_register = Get_target_Register(instruction);
        }else{                                                  //se não for zero, então é um valor imediato
            data.addressRAMResult = Get_immediate(instruction); 
        }
    }

    return;
}

void Control_Unit::Execute(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int& counterForEnd,bool& programEnd, MainMemory& ram,int id){
    if(data.op == "ADD" ||  data.op == "SUB" || data.op == "MUL" || data.op == "DIV"){
        Execute_Aritmetic_Operation(registers, data);
    }else if(data.op == "BEQ" || data.op == "J" || data.op == "BNE" || data.op == "BGT" || data.op == "BGTI" || data.op == "BLT" || data.op == "BLTI"){
        Execute_Loop_Operation(registers, data, counter,counterForEnd,programEnd,ram, id);
    }
    else if( data.op == "PRINT" ){
        if(PERMISSIONS2[1] == 1)
        {
            WAITING_QUEUE2[1].push(id);
            while(WAITING_QUEUE2[1].front() != id && PERMISSIONS2[1] == 1){}
            if(!WAITING_QUEUE2[1].empty()){WAITING_QUEUE2[1].pop();}
        }
        PERMISSIONS2[1] = 1;
        Execute_Operation(registers,data,id);
        PERMISSIONS2[1] = 0;
    }

}

void Control_Unit::Memory_Acess(REGISTER_BANK &registers,Instruction_Data &data, MainMemory &memory, int id){
    
    string nameregister = this->map.mp[data.target_register];

    if(data.op == "LW"){
        if(PERMISSIONS2[0] == 1)
        {
            WAITING_QUEUE2[0].push(id);
            while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
            if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
        }
        PERMISSIONS2[0] = 1;

        int decimal_addr = ConvertToDecimalValue(stoul(data.addressRAMResult));
        registers.acessoEscritaRegistradores[nameregister](memory.ReadMem(decimal_addr));
        PERMISSIONS2[0] = 0;
    }
    if(data.op == "LA" || data.op == "LI"){
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
        registers.acessoEscritaRegistradores[nameregister](decimal_value);
    }
    else if(data.op == "PRINT" && data.target_register == ""){
        if(PERMISSIONS2[0] == 1)
        {
            WAITING_QUEUE2[0].push(id);
            while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
            if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
        }
        PERMISSIONS2[0] = 1;
        int decimal_addr = ConvertToDecimalValue(stoul(data.addressRAMResult));
        uint32_t value = memory.ReadMem(decimal_addr);
        PERMISSIONS2[0] = 0;

        if(PERMISSIONS2[1] == 1)
        {
            WAITING_QUEUE2[1].push(id);
            while(WAITING_QUEUE2[1].front() != id && PERMISSIONS2[1] == 1){}
            if(!WAITING_QUEUE2[1].empty()){WAITING_QUEUE2[1].pop();}
        }
        PERMISSIONS2[1] = 1;
        printf("PROGRAM PRINT [PROCESSO %d]: %" PRIu32 "\n",id , value); //ENDEREÇO DE MEMORIA
        PERMISSIONS2[1] = 0;
    }

    return;
}

void Control_Unit::Write_Back(Instruction_Data &data, MainMemory &memory,REGISTER_BANK &registers, int id, int &LAST_ADDRESS){

    string nameregister = this->map.mp[data.target_register];
    
    if(data.op == "SW"){
        if(PERMISSIONS2[2] == 1)
        {
            WAITING_QUEUE2[2].push(id);
            while(WAITING_QUEUE2[2].front() != id && PERMISSIONS2[2] == 1){}
            if(!WAITING_QUEUE2[2].empty()){WAITING_QUEUE2[2].pop();}
        }
        PERMISSIONS2[2] = 1;
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));

        memory.WriteMem(decimal_value, registers.acessoLeituraRegistradores[nameregister]());
        LAST_ADDRESS++;
        PERMISSIONS2[2] = 0;
    }

    return;

}

//VERIFICA SE TEM ALGO, CASO TENHA => PCB.STATE = WAIT => ESPERA LIBERAR O RECURSO => RETORNA PRA LISTA DE PRONTOS


string Control_Unit::Identificacao_instrucao(uint32_t instruction, REGISTER_BANK &registers){

    string instrucao = bitset<32>(instruction).to_string();
    string string_instruction = instrucao;
    string opcode = "";
    string instruction_type = "";

    for(int i = 0; i < 6; i++){
        opcode += string_instruction[i];
    }
    //instrução do tipo I
    if (opcode == this->instructionMap.at("la")) {              // LOAD from vector
        instruction_type = "LA";
    } else if (opcode == this->instructionMap.at("lw")) {       // LOAD
        instruction_type = "LW";
    } else if (opcode == this->instructionMap.at("j")) {        // JUMP
        instruction_type = "J";
    } else if (opcode == this->instructionMap.at("sw")) {       // STORE
        instruction_type = "SW";
    } else if (opcode == this->instructionMap.at("beq")) {      // EQUAL
        instruction_type = "BEQ";
    } else if (opcode == this->instructionMap.at("blt")) {      // LESS THAN
        instruction_type = "BLT";
    } else if (opcode == this->instructionMap.at("blti")) {     // LESS THAN OR EQUAL
        instruction_type = "BLTI";
    } else if (opcode == this->instructionMap.at("bgt")) {      // GREATER THAN
        instruction_type = "BGT";
    } else if (opcode == this->instructionMap.at("bgti")) {     // GREATER THAN OR EQUAL
        instruction_type = "BGTI";
    }
    else if (opcode == this->instructionMap.at("print")) {    
        instruction_type = "PRINT";
    }
    else if (opcode == this->instructionMap.at("li")) {    
        instruction_type = "LI";                                // LOAD IMMEDIATE
    }

    // instruções do tipo R

    if (opcode == this->instructionMap.at("add")) {              
        instruction_type = "ADD";
            //cout << this->instructionMap.at("add")<< "opcode soma:" << opcode << endl;

    } else if (opcode == this->instructionMap.at("sub")) {       
        instruction_type = "SUB";
    } else if (opcode == this->instructionMap.at("mult")) {       
        instruction_type = "MULT";
    } else if (opcode == this->instructionMap.at("div")) {      
        instruction_type = "DIV";
    }

    return instruction_type;
} 

string Control_Unit::Get_immediate(const uint32_t instruction)
{
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 16; i < 32; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_destination_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 16; i < 21; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_target_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 11; i < 16; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_source_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 6; i < 11; i++){
        code += copia_instrucao[i];
    }

    return code;
}

void Control_Unit::Execute_Aritmetic_Operation(REGISTER_BANK &registers,Instruction_Data &data){

        string nameregistersource = this->map.mp[data.source_register];
        string nametargetregister = this->map.mp[data.target_register];
        string nameregisterdestination = this->map.mp[data.destination_register]; 
        ALU alu;
        if(data.op == "ADD"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = ADD;
            alu.calculate();
            //cout << "valor de A:" << alu.A << endl;
            //cout << "valor de B:" << alu.B << endl;
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout<< "resultado soma:" <<registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "SUB"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = SUB;
            //cout << "valor de A:" << alu.A << endl;
            //cout << "valor de B:" << alu.B << endl;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout << "resultado subtração:" << registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "MUL"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = MUL;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout << "resultado multiplicação:" << registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "DIV"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = DIV;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
        }

        return;
}

void Control_Unit::Execute_Loop_Operation(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int& counterForEnd, bool& programEnd, MainMemory& ram, int id){
    
    string nameregistersource = this->map.mp[data.source_register];
    string nametargetregister = this->map.mp[data.target_register];
    string nameregisterdestination = this->map.mp[data.destination_register];
    ALU alu;
    if(data.op == "BEQ"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BEQ;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BNE"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BNE;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "J"){
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
        registers.pc.write(decimal_value);
        if(PERMISSIONS2[0] == 1)
        {
            WAITING_QUEUE2[0].push(id);
            while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
            if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
        }
        PERMISSIONS2[0] = 1;
        registers.ir.write(ram.ReadMem(registers.pc.read()));
        PERMISSIONS2[0] = 0;

        counter = 0;
        counterForEnd = 5;
        programEnd = false;
    }else if(data.op == "BLT"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BLT;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BLTI"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BLTI;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BGT"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BGT;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BGTI"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BGTI;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            if(PERMISSIONS2[0] == 1)
            {
                WAITING_QUEUE2[0].push(id);
                while(WAITING_QUEUE2[0].front() != id && PERMISSIONS2[0] == 1){}
                if(!WAITING_QUEUE2[0].empty()){WAITING_QUEUE2[0].pop();}
            }
            PERMISSIONS2[0] = 1;
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            PERMISSIONS2[0] = 0;
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }
    return;
}

void Control_Unit::Execute_Operation(REGISTER_BANK &registers,Instruction_Data &data,int id){
    string nameregister = this->map.mp[data.target_register];

    if(data.op == "PRINT" && data.target_register != ""){
        printf("PROGRAM PRINT [PROCESSO %d]: %" PRIu32 "\n", id ,  registers.acessoLeituraRegistradores[nameregister]());
    }
}

string Control_Unit::Pick_Code_Register_Load(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 11; i < 16; i++){
        code += copia_instrucao[i];
    }

    return code;
}