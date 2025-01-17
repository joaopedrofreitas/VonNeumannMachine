#include"./cpu/Core.cpp"
#include <pthread.h>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    MainMemory ram = MainMemory(2048, 2048);
    pthread_t threads[(argc-2)];
    ThreadArgs threadArgs[(argc-2)];
    vector<int> Bilhetes;

    for (int i = 0; i < (argc-2); i++) {

        PCB processo = loadProgram(argv[i + 1], ram, i, LAST_ADDRESS, WAITING_QUEUE[2], PERMISSIONS[2]);

        for(int i=Bilhetes.size(); i < (LAST_ADDRESS/3);i++){
            processo.Tickets.push_back(i);
            Bilhetes.push_back(i);
        }
        READY_QUEUE.push(processo);
        PRIORITY_READY_QUEUE.push(processo); // SJF
    }

    if(argv[argc-1][0] == '0'){
        for (int i = 0; i < (argc-2); i++) {
            threadArgs[i] = {i, &ram, &READY_QUEUE.front()};
            if (pthread_create(&threads[i], nullptr, CoreFunction, (void*)&threadArgs[i]) != 0) {
                std::cerr << "Erro ao criar a thread " << i << std::endl;
                return 1;
            }
            if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
        }

        for (int i = 0; i < (argc-2); i++) {
            pthread_join(threads[i], nullptr);
        }

    }
    else if(argv[argc-1][0]== '1'){
        CURRENT_TICKET = random_number(0, Bilhetes.size());

        for (int i = 0; i < (argc-2); i++) {
            threadArgs[i] = {i, &ram, &READY_QUEUE.front(),static_cast<int>(Bilhetes.size())};
            if (pthread_create(&threads[i], nullptr, CoreFunction_Lottery, (void*)&threadArgs[i]) != 0) {
                std::cerr << "Erro ao criar a thread " << i << std::endl;
                return 1;
            }
            if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
        }

        for (int i = 0; i < (argc-2); i++) {
            pthread_join(threads[i], nullptr);
        }

    }
    else if(argv[argc-1][0]== '2'){

         for (int i = 0; i < (argc-2); i++) {
            threadArgs[i] = {i, &ram, &READY_QUEUE.front()};
            if (pthread_create(&threads[i], nullptr, CoreFunction_SJF, (void*)&threadArgs[i]) != 0) {
                std::cerr << "Erro ao criar a thread " << i << std::endl;
                return 1;
            }
            if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
        }

        for (int i = 0; i < (argc-2); i++){
            pthread_join(threads[i], nullptr);
        }
    }


    return 0;
}
