#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include "../cpu/REGISTER.h"
#include "../cpu/REGISTER_BANK.h"
using namespace std;

enum ProcessState { 
    READY, 
    RUNNING, 
    WAITING,  
};

// PRINT.READ,STORE,LOAD => Recursos   --  WAIT 
// Memoria => Recusos                  --  WAIT

class PCB {
public:
    int process_id;                                  // ID único do processo     -> ID 
    int base_address;                                // Endereço base            -> Endereço que vai começar 
    int QUANTUM;                                     // QUANTUM                  -> Tempo necessário para completar o processo
    int COST;                                        // COST                     -> Usado no SJF
    int program_counter;                             // Instrução atual          -> Endereço da instrução
    ProcessState state;                              // Estado do processo       -> READY, RUNNING, WAITING, TERMINATED  
    vector<pair<REGISTER_BANK, int>> registers;      // Banco de registradores   -> (REGISTRADOR - VALOR)  
    vector<int> Tickets;                             // Bilhetes                 -> Para o Lottery Scheduling
    
    PCB(int id, int exec_time, int base_address,int Cost)
        : process_id(id), state(READY), program_counter(base_address), QUANTUM(exec_time), base_address(base_address), COST(Cost)/*,last_address(last_address)*/{}
};