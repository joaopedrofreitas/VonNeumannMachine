#include "./cpu/REGISTER_BANK.h"
#include "./cpu/CONTROL_UNIT.h"
#include "./memory/MAINMEMORY.h"
#include "./loader.h"
#include <cstdint>
#include <queue>
#include <atomic>
#include <pthread.h>

#define N_PROCESS 3
using namespace std;

queue<PCB> READY_QUEUE;
int CONTADOR_RUNNING = 0;
queue<PCB> WAITING_QUEUE;

vector<bool> PERMISSIONS = {0,0,0,0}; //LOAD | PRINT | READ | STORE

struct ThreadArgs {
    int core_id;
    MainMemory* ram;
    PCB* Processo;
};

void* CoreFunction(void* args){
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
    
   if (CONTADOR_RUNNING < 2) {
        Processo.state = RUNNING;
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    } else {
        while(CONTADOR_RUNNING >= 2 && READY_QUEUE.front().process_id != Processo.process_id){}
        CONTADOR_RUNNING++;
        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    while (counterForEnd > 0) {
        if (counter >= 4 && counterForEnd >= 1) {
            UC.Write_Back(UC.data[counter - 4], ram, registers);
        }
        if (counter >= 3 && counterForEnd >= 2) {
            UC.Memory_Acess(registers, UC.data[counter - 3], ram);
        }
        if (counter >= 2 && counterForEnd >= 3) {
            UC.Execute(registers, UC.data[counter - 2], counter, counterForEnd, endProgram, ram);
        }
        if (counter >= 1 && counterForEnd >= 4) {
            UC.Decode(registers, UC.data[counter - 1]);
        }
        if (counter >= 0 && counterForEnd == 5) {
            UC.data.push_back(data);
            UC.Fetch(registers, endProgram, ram, Processo);
        }

        counter += 1;
        clock += 1;

        if (endProgram == true) {
            counterForEnd = -1;
        }
        else{
            if((Processo.QUANTUM - timestamp) == 0) {
                CONTADOR_RUNNING--;            
                READY_QUEUE.push(Processo);
                while(CONTADOR_RUNNING >= 2 && READY_QUEUE.front().process_id != Processo.process_id){}
                CONTADOR_RUNNING++;
                if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
            }
        }
    }
    //registers.print_registers();
    std::cout << "Core " << core_id << " finalizado.\n";
    CONTADOR_RUNNING--;

    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    int LAST_ADDRESS = -1;

    MainMemory ram = MainMemory(2048, 2048);
    pthread_t threads[N_PROCESS];
    ThreadArgs threadArgs[N_PROCESS];

    // Carrega os processos na READY_QUEUE
    for (int i = 0; i < N_PROCESS; i++) {
        PCB processo = loadProgram(argv[i + 1], ram, i, LAST_ADDRESS);
        READY_QUEUE.push(processo);
    }

    // Cria as threads
    for (int i = 0; i < N_PROCESS; i++) {
        threadArgs[i] = {i, &ram, &READY_QUEUE.front()};

        if (pthread_create(&threads[i], nullptr, CoreFunction, (void*)&threadArgs[i]) != 0) {
            std::cerr << "Erro ao criar a thread " << i << std::endl;
            return 1;
        }

        if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
    }

    // Aguarda o término das threads
    for (int i = 0; i < N_PROCESS; i++) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}
