#include "REGISTER_BANK.h"
#include "CONTROL_UNIT.h"
#include "../memory/MAINMEMORY.h"
#include "../loader.h"
#include <cstdint>
#include <queue>
#include <atomic>
#include <chrono>
#include <random>

#define N_PROCESS 2 
using namespace std;

queue<PCB> READY_QUEUE;
int CONTADOR_RUNNING = 0;
vector<queue<int>> WAITING_QUEUE(3); //LOAD | PRINT | STORE -> I/O REQUESTS
int LAST_ADDRESS = 0;
int CURRENT_TICKET = 0;

vector<int> PERMISSIONS = {0,0,0};   //LOAD | PRINT | STORE -> I/O REQUESTS

int random_number(int min, int max) {
    // Gera um motor aleatório com base no tempo atual
    std::random_device rd;  // Dispositivo de entropia
    std::mt19937 gen(rd()); // Mersenne Twister, inicializado com entropia
    std::uniform_int_distribution<> distr(min, max); // Distribuição uniforme entre min e max

    return distr(gen);
}



struct ThreadArgs {
    int core_id;
    MainMemory* ram;
    PCB* Processo;
    int max;
};

void* CoreFunction(void* args){      //FCFS
    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    MainMemory& ram = *(coreArgs->ram);
    PCB& Processo = *(coreArgs->Processo);

    Control_Unit UC;
    REGISTER_BANK registers;
    Instruction_Data data;
    bool endProgram = false;

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int timestamp = 0;

    auto start_time = chrono::high_resolution_clock::now();
    
   if (CONTADOR_RUNNING < N_PROCESS) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    } else {
        while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != Processo.process_id){}
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers, Processo.process_id, LAST_ADDRESS);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram, Processo.process_id);
        }
        if (counter >= 2 && counterForEnd >= 3) {
            UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram, Processo.process_id);
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo, Processo.process_id);
        }

        counter += 1;
        clock += 1;
        timestamp += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - timestamp) == 0) {
                CONTADOR_RUNNING--;            
                READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != Processo.process_id){}
                CONTADOR_RUNNING++;
                if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << fixed << setprecision(7);
    cout << "Core " << core_id << " finalizado. Tempo de execução: " << elapsed_time.count() << " segundos.\n";

    CONTADOR_RUNNING--;
    pthread_exit(nullptr);
    
}


void* CoreFunction_Lottery(void* args){      //Loteria
    ThreadArgs* coreArgs = (ThreadArgs*)args;

    int core_id = coreArgs->core_id;
    MainMemory& ram = *(coreArgs->ram);
    PCB& Processo = *(coreArgs->Processo);
    int max = coreArgs->max;

    Control_Unit UC;
    REGISTER_BANK registers;
    Instruction_Data data;
    bool endProgram = false;

    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    int timestamp = 0;

    auto start_time = chrono::high_resolution_clock::now();

   if (CONTADOR_RUNNING < N_PROCESS) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    } else {
        cout<<"VALOR DO TICKET: "<<CURRENT_TICKET<<endl;
        auto K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);
        while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != Processo.process_id && K == end(Processo.Tickets)){K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);}
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers, Processo.process_id, LAST_ADDRESS);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram, Processo.process_id);
        }
        if (counter >= 2 && counterForEnd >= 3) {
            UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram, Processo.process_id);
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo, Processo.process_id);
        }

        counter += 1;
        clock += 1;
        timestamp += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - timestamp) == 0) {
                cout<<"OCORREU CHAVEAMENTO -> VALOR DO TICKET: "<<CURRENT_TICKET<<endl;
                CURRENT_TICKET = random_number(0, max);
                auto K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);
                CONTADOR_RUNNING--;            
                READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= N_PROCESS && READY_QUEUE.front().process_id != Processo.process_id && K == end(Processo.Tickets)){K = find(begin(Processo.Tickets), end(Processo.Tickets),CURRENT_TICKET);}
                CONTADOR_RUNNING++;
                if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << fixed << setprecision(7);
    cout << "Core " << core_id << " finalizado. Tempo de execução: " << elapsed_time.count() << " segundos.\n";

    CONTADOR_RUNNING--;
    pthread_exit(nullptr);
    
}