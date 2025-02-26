#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <iostream>
#include "ALU.h"
#include "REGISTER_BANK.h"
#include <string>
#include <vector>
#include"HashRegister.h"
#include"unordered_map"
#include"../memory/MAINMEMORY.h"
#include"../memory/CACHE.h"
#define NO_COLOR "\x1b[0;0m"
#define BRIGHT_GREEN "\x1b[92;1m"
#define BRIGHT_CYAN "\x1b[96;1m"
#include <cstdint>
#include <cmath>

using namespace std;

struct Instruction_Data{
    string source_register;
    string target_register;
    string destination_register;
    string op;
    string addressRAMResult;
};

struct Control_Unit{

    operation op;

    vector<Instruction_Data> data;

    Map map;
   
    unordered_map<string, string> instructionMap = {
        {"add", "000000"},
        {"and", "000001"},
        {"div", "000010"},
        {"mult","000011"},
        {"sub", "000100"},
        {"beq", "000101"},
        {"bne", "000110"},
        {"bgt", "000111"},
        {"bgti","001000"},
        {"blt", "001001"},
        {"blti","001010"},
        {"j", "001011"},
        {"lw", "001100"},
        {"sw", "001101"},
        {"li", "001110"},
        {"la", "001111"},
        {"print", "010000"},
        {"end", "111111"}
    };

    unordered_map<string,string> Operators ={
        {"ADD", "+"},
        {"SUB","-"},
        {"MUL","*"},
        {"DIV","/"}
    };


    string Get_immediate(const uint32_t instruction);
    string Pick_Code_Register_Load(const uint32_t instruction);
    string Get_destination_Register(const uint32_t instruction);
    string Get_target_Register(const uint32_t instruction);
    string Get_source_Register(const uint32_t instruction);

    string Identificacao_instrucao(uint32_t instruction, REGISTER_BANK &registers);
    void Fetch(REGISTER_BANK &registers, bool &endProgram,MainMemory &ram,PCB &pcb, int id);
    void Decode(REGISTER_BANK &registers, Instruction_Data &data);
    void Execute_Aritmetic_Operation(REGISTER_BANK &registers,Instruction_Data &data, Cache_Memory& Cache);
    void Execute_Operation(REGISTER_BANK &registers,Instruction_Data &data,int id);
    void Execute_Loop_Operation(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int &counterForEnd, bool& endProgram, MainMemory& ram,Cache_Memory& Cache,int id); 
    void Execute(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int& counterForEnd,bool& programEnd, MainMemory& ram,Cache_Memory& Cache,int id);
    void Memory_Acess(REGISTER_BANK &registers,Instruction_Data &data, MainMemory &memory, int id);
    void Write_Back(Instruction_Data &data, MainMemory &memory,REGISTER_BANK &registers, int id,int &LAST_ADDRESS);
};

#endif