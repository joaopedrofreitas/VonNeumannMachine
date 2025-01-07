#include"./memory/MAINMEMORY.h"
#include <string>

PCB loadProgram(const std::string& inputFile, MainMemory & ram, int id, int &LAST_ADDRESS, queue<int>& WAITING_QUEUE, int& PERMISSIONS); 
