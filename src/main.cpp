#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"
#include <cstdint>
#include <queue>

#define N_PROCESS 1
using namespace std;

struct ThreadArgs {
    int core_id;
    Control_Unit* UC;
    REGISTER_BANK* registers;
    MainMemory* ram;
    Instruction_Data* data;
    bool* endProgram;
    std::queue<PCB>* Fila_Prontos;
};


void* CoreFunction(void* args){
    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    Control_Unit& UC = *(coreArgs->UC);
    REGISTER_BANK& registers = *(coreArgs->registers);
    MainMemory& ram = *(coreArgs->ram);
    Instruction_Data& data = *(coreArgs->data);
    bool& endProgram = *(coreArgs->endProgram);
    std::queue<PCB>& Fila_Prontos = *(coreArgs->Fila_Prontos);

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int timestamp = 0;

   while(counterForEnd > 0){
            if(counter >= 4 && counterForEnd >= 1){
                //chamar a instrução de write back
                UC.Write_Back(UC.data[counter - 4],ram,registers);
            }
            if(counter >= 3 && counterForEnd >= 2){
                //chamar a instrução de memory_acess da unidade de controle
                UC.Memory_Acess(registers, UC.data[counter - 3],ram);
            }
            if(counter >= 2 && counterForEnd >= 3){
                //chamar a instrução de execução da unidade de controle
                UC.Execute(registers,UC.data[counter - 2], counter, counterForEnd,endProgram,ram);
            }
            if(counter >= 1 && counterForEnd >= 4){
                //chamar a instrução de decode da unidade de controle
                UC.Decode(registers, UC.data[counter-1]);
            }
            if(counter >= 0 && counterForEnd == 5){
                //chamar a instrução de fetch da unidade de controle
                UC.data.push_back(data) ;
                UC.Fetch(registers, endProgram,ram);
            }
            
            counter += 1;
            clock += 1;
            timestamp+= 1;

            if(endProgram == true){
                counterForEnd =- 1;
            }
            //pcb.QUANTUM-timestamp >=0
        }

    std::cout << "Core " << core_id << " finalizado.\n";
    pthread_exit(nullptr);
}




int main(int argc, char* argv[]){

    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
      return 1;
    }

    MainMemory ram = MainMemory(2048,2048);				  
    REGISTER_BANK registers;
    Control_Unit UC;
    queue<PCB> Fila_Prontos;

    bool endProgram = false;
    Instruction_Data data;


    for(int i=0; i < N_PROCESS; i++){
        PCB processo = loadProgram(argv[i+1],ram,i);
        Fila_Prontos.push(processo);
    }
    
    pthread_t  threads[N_PROCESS];
    ThreadArgs threadArgs[N_PROCESS];

    for (int i = 0; i < N_PROCESS; i++) {
        threadArgs[i] = {i, &UC, &registers, &ram, &data, &endProgram, &Fila_Prontos};
        if (pthread_create(&threads[i], nullptr, CoreFunction, (void*)&threadArgs[i]) != 0) {
            std::cerr << "Erro ao criar a thread " << i << std::endl;
            return 1;
        }
    }

    for (int i = 0; i < N_PROCESS; i++) {
        pthread_join(threads[i], nullptr);
    }

    std::cout << "Simulação multicore finalizada.\n";

    return 0;
}



 /*numcores=2;
    pthread thread;
    // PIPELINE - CORE 1
    ThreadsVetor<thread> Vthread;
    for(int i=0; i<2;i++){
        Vthread.emplace_back(Pipeline, i, std::ref(UC), num_cores);
    }*/