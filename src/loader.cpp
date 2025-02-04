#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
#include"./memory/MAINMEMORY.h"
#include"loader.h"

const int MEMORY_SIZE = 2048*2048; // 32-bit address space

std::string padName(const std::string& name) {
    return name + std::string(16 - name.length(), '#');
}

PCB loadProgram(const std::string& inputFile, MainMemory & ram, int id, int &LAST_ADDRESS, queue<int>& WAITING_QUEUE, int& PERMISSIONS) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }

    std::unordered_map<std::string, int> labelAddresses;
    std::unordered_map<std::string, int> variableAddresses;
    std::vector<std::string> instructions;
    int address = LAST_ADDRESS;
    
    int QUANTUM = 0;
    
    std::string line;

    // Read instructions and data
    while (std::getline(file, line)) {
      std::string trimmedLine = line;
      trimmedLine.erase(trimmedLine.find_last_not_of(" \n\r\t") + 1);
        
      // data section
      if (trimmedLine.find(".data") != std::string::npos) {
        while (std::getline(file, line)) {
            std::istringstream dataStream(line);
            std::string variableName;
            std::string values;
            std::string value;

          // Extract variable name and value from the format "var: value"
          if (dataStream >> variableName) {
            size_t colonPos = variableName.find(':');
            if (colonPos != std::string::npos) {
                variableName = variableName.substr(0, colonPos); 
                variableAddresses[padName(variableName)] = address;

                std::getline(dataStream, values);
                std::istringstream valueStream(values);

                while (std::getline(valueStream, value, ',')) {
                    if (address >= MEMORY_SIZE) {
                        std::cerr << "Memory overflow while allocating vector data." << std::endl;
                        exit(1);
                    }
                    // Convert the value to int and store it in memory
                    int intValue = std::stoi(value);
                    if(PERMISSIONS == 1)
                    {
                        WAITING_QUEUE.push(id);
                        while(WAITING_QUEUE.front() != id && PERMISSIONS == 1){}
                        if(!WAITING_QUEUE.empty()){WAITING_QUEUE.pop();}
                    }
                    PERMISSIONS = 1;
                    ram.WriteMem(address,intValue);
                    PERMISSIONS = 0;

                    address += 1; 
                }
            }
          }    
        }
      break; 
    }
    
    else if (trimmedLine.find(":") != std::string::npos) {
        size_t colonPos = trimmedLine.find(":");
        std::string label = trimmedLine.substr(0, colonPos);
        labelAddresses[padName(label)] = address; 

         //std::cout << "Label: " << padName(label) << " Address: " << labelAddresses[padName(label)] << std::endl;
         if (std::getline(file, line)) {
            instructions.push_back(line); // Store instruction
            address += 1; 
        }
    }
    else {
        instructions.push_back(trimmedLine);
        address += 1; 
      }
    }

    
    int memAddress = LAST_ADDRESS;
    int InitialAdress = LAST_ADDRESS;
    
    for (auto instruction : instructions) {
        for (const auto& [label, addr] : labelAddresses) {
            size_t pos = instruction.find(label);
            if (pos != std::string::npos) {
                instruction.replace(pos, label.length(), std::bitset<16>(addr).to_string());
            }
        }
        for (const auto& [varName, addr] : variableAddresses) {
            size_t pos = instruction.find(varName);
            if (pos != std::string::npos) {
                instruction.replace(pos, varName.length(), std::bitset<16>(addr).to_string());
            }
        }
        
        size_t pos = instruction.find("#");
        if (pos != std::string::npos) {
            std::cerr << "Can't resolve symbol at instruction: " << instruction << std::endl; 
        }

        
        try {
            if(PERMISSIONS == 1)
            {
                WAITING_QUEUE.push(id);
                while(WAITING_QUEUE.front() != id && PERMISSIONS == 1){}
                if(!WAITING_QUEUE.empty()){WAITING_QUEUE.pop();}
            }
            PERMISSIONS = 1;
            ram.WriteMem(memAddress, std::stoul(instruction, nullptr, 2));
            PERMISSIONS = 0;
        } catch (const std::exception& e) {
            std::cerr << "Conversion error at: " << instruction << std::endl;
        }
        
        memAddress++;
    }

    LAST_ADDRESS = address+ 1;
    QUANTUM = 10;         
    int STATE = 0;
    int COST = instructions.size();

    //Output the loaded memory for verification
    // for (size_t i = 0; i < 130; ++i) {
    //    std::cout << "Address " << (i) << ": " << std::bitset<32>(ram.ReadMem(i)) << std::endl;
    // }

    PCB processo = PCB(id,QUANTUM,InitialAdress,COST,instructions);
    return processo;
}