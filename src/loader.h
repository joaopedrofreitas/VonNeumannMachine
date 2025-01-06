#ifndef LOADER_HPP
#define LOADER_HPP

#include"./memory/MAINMEMORY.h"
#include <string>

PCB loadProgram(const std::string& inputFile, MainMemory & ram, int id, int &LAST_ADDRESS); 

#endif