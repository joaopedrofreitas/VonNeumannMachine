#include "REGISTER_BANK.h"
#include "CONTROL_UNIT.h"
#include "../memory/MAINMEMORY.h"
#include "../memory/CACHE.h"
#include "../loader.h"
#include <cstdint>
#include <queue>
#include <atomic>
#include <chrono>
#include <random>
#include <iomanip>  
#include <algorithm>

#define N_PROCESS 2                 // Numero max de pra cada Core.
using namespace std;


struct ComparePCB {
    bool operator()(const PCB& a, const PCB& b) {
        return a.COST > b.COST;     // PCB com menor COST tem maior prioridade
    }
};

queue<PCB> READY_QUEUE;
priority_queue<PCB, vector<PCB>, ComparePCB> PRIORITY_READY_QUEUE;
int CONTADOR_RUNNING = 0;
vector<queue<int>> WAITING_QUEUE(3); //LOAD | PRINT | STORE -> I/O REQUESTS
//vector<map<string,int>> Instruction_set;
int LAST_ADDRESS = 0;
int CURRENT_TICKET = 0;
int RUNNING_PROCESS_ID = 0;

vector<int> PERMISSIONS = {0,0,0};   //LOAD | PRINT | STORE -> I/O REQUESTS

int random_number(int min, int max) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(min, max); 

    return distr(gen);
}

struct ThreadArgs {
    int core_id;
    MainMemory* ram;
    Cache_Memory* Cache;
    PCB* Processo;
    int max;
};

void* CoreFunction(void* args){      //FCFS
    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    MainMemory& ram = *(coreArgs->ram);
    Cache_Memory& Cache = *(coreArgs-> Cache);
    PCB& Processo = *(coreArgs->Processo);

    Control_Unit UC;
    REGISTER_BANK registers;
    Instruction_Data data;
    bool endProgram = false;

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int aux = 0;

    auto start_time = chrono::high_resolution_clock::now();
    
   if (CONTADOR_RUNNING < N_PROCESS) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    } else {
        while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != core_id){}
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers, core_id, LAST_ADDRESS);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram, core_id);
        }
        if (counter >= 2 && counterForEnd >= 3) {
            UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram, Cache,core_id);
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo, core_id);
        }

        counter += 1;
        clock += 1;
        aux += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - aux) == 0) {

                CONTADOR_RUNNING--;            
                READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != core_id){}
                CONTADOR_RUNNING++;
                if(!READY_QUEUE.empty()){READY_QUEUE.pop();}

            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> timestamp = end_time - start_time;

    printf("Core %d finalizado. Tempo de execução: %.7f segundos.\n", core_id, timestamp.count());

    CONTADOR_RUNNING--;
    pthread_exit(nullptr);
    
}


void* CoreFunction_Lottery(void* args){      //Loteria
    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    MainMemory& ram = *(coreArgs->ram);
    Cache_Memory& Cache = *(coreArgs-> Cache);
    PCB& Processo = *(coreArgs->Processo);
    int max = coreArgs->max;

    Control_Unit UC;
    REGISTER_BANK registers;
    Instruction_Data data;
    bool endProgram = false;

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int aux = 0;

    auto start_time = chrono::high_resolution_clock::now();

   if (CONTADOR_RUNNING < N_PROCESS) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    } else {
        auto K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);
        while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != core_id && K == end(Processo.Tickets)){K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);}
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers, core_id, LAST_ADDRESS);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram, core_id);
        }
        if (counter >= 2 && counterForEnd >= 3) {
           UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram, Cache,core_id);
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo, core_id);
        }

        counter += 1;
        clock += 1;
        aux += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - aux) == 0) {

                //cout<<"OCORREU CHAVEAMENTO -> VALOR DO TICKET: "<<CURRENT_TICKET<<endl;
                CURRENT_TICKET = random_number(0, max);
                auto K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);
                CONTADOR_RUNNING--;            
                READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != core_id && K == end(Processo.Tickets)){K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);}
                CONTADOR_RUNNING++;
                if(!READY_QUEUE.empty()){READY_QUEUE.pop();}

            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> timestamp = end_time - start_time;

    printf("Core %d finalizado. Tempo de execução: %.7f segundos.\n", core_id, timestamp.count());

    CONTADOR_RUNNING--;
    pthread_exit(nullptr);
    
}


void* CoreFunction_SJF(void* args){      //SJF

    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    MainMemory& ram = *(coreArgs->ram);
    Cache_Memory& Cache = *(coreArgs-> Cache);
    PCB& Processo = *(coreArgs->Processo);

    Control_Unit UC;
    REGISTER_BANK registers;
    Instruction_Data data;
    bool endProgram = false;

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int aux = 0;

    auto start_time = chrono::high_resolution_clock::now();
    
   if (CONTADOR_RUNNING < N_PROCESS) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!PRIORITY_READY_QUEUE.empty()){PRIORITY_READY_QUEUE.pop();}
    } else {
        while(CONTADOR_RUNNING >= N_PROCESS && PRIORITY_READY_QUEUE.top().process_id != core_id){PRIORITY_READY_QUEUE.push(Processo);}
        CONTADOR_RUNNING++;
        if(!PRIORITY_READY_QUEUE.empty()){PRIORITY_READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers, core_id, LAST_ADDRESS);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram, core_id);
        }
        if (counter >= 2 && counterForEnd >= 3) {
            UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram, Cache,core_id);
            Processo.COST-=1;
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo, core_id);
        }

        counter += 1;
        clock += 1;
        aux += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - aux) == 0 && counterForEnd != 0) {

                CONTADOR_RUNNING--;            
                PRIORITY_READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= N_PROCESS && PRIORITY_READY_QUEUE.top().process_id != core_id){PRIORITY_READY_QUEUE.push(Processo);}
                CONTADOR_RUNNING++;
                if(!PRIORITY_READY_QUEUE.empty()){PRIORITY_READY_QUEUE.pop();}

            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> timestamp = end_time - start_time;
    
    printf("Core %d finalizado. Tempo de execução: %.7f segundos.\n", core_id, timestamp.count());

    CONTADOR_RUNNING--;
    pthread_exit(nullptr);
    
}