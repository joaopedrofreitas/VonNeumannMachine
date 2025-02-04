#include"./cpu/Core.cpp"
#include <pthread.h>

float calculateSimilarity(const PCB& p1, const PCB& p2) { // Fazer o calculo de Similiridade entre os processos.
    int total_Instructions = max(p1.Instructions.size(), p2.Instructions.size());
    if(total_Instructions == 0) return 0.0f;

    int matches = 0;
    for(int i = 0; i < min(p1.Instructions.size(), p2.Instructions.size()); i++) {
        if(p1.Instructions[i] == p2.Instructions[i]) {
            matches++;
        }
    }
    
    return static_cast<float>(matches) / total_Instructions * 100.0f;
}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    MainMemory ram = MainMemory(2048, 2048);
    Cache_Memory Cache;
    pthread_t threads[(argc-2)];
    ThreadArgs threadArgs[(argc-2)];
    vector<int> Bilhetes;
    vector<PCB> processes;
    vector<PCB> processList;

    for (int i = 0; i < (argc-2); i++) {

        PCB processo = loadProgram(argv[i + 1], ram, i, LAST_ADDRESS, WAITING_QUEUE[2], PERMISSIONS[2]);

        for(int i=Bilhetes.size(); i < (LAST_ADDRESS/3);i++){
            processo.Tickets.push_back(i);
            Bilhetes.push_back(i);
        }
        READY_QUEUE.push(processo);
        PRIORITY_READY_QUEUE.push(processo); // SJF
    }

    // while(!READY_QUEUE.empty()) {
    //     processes.push_back(READY_QUEUE.front());
    //     READY_QUEUE.pop();
    // }

    // for(int i = 0; i < processes.size(); i++) {
    //     for(int j = i+1; j < processes.size(); j++) {
    //         float sim_ij = calculateSimilarity(processes[i], processes[j]);
    //         float sim_i_next = (i < processes.size()-1) ? 
    //             calculateSimilarity(processes[i], processes[i+1]) : 0;
            
    //         if(sim_ij > sim_i_next) {
    //             swap(processes[i+1], processes[j]);
    //             break;
    //         }
    //     }
    // }

    // for(const auto& p : processes) {
    //     READY_QUEUE.push(p);
    // }

    // while(!READY_QUEUE.empty()) {
    //     processList.push_back(READY_QUEUE.front());
    //     READY_QUEUE.pop();
    // }

    // for(int i = 0; i < processList.size()-1; i++) {
    //     float similarity = calculateSimilarity(processList[i], processList[i+1]);
    //         cout << "Similaridade entre Processo " << processList[i].process_id 
    //               << " e Processo " << processList[i+1].process_id << ": "
    //               << fixed << setprecision(2) 
    //               << similarity << "%\n";
    // }


    if(argv[argc-1][0] == '0'){
        for (int i = 0; i < (argc-2); i++) {
            threadArgs[i] = {i, &ram, &Cache,&READY_QUEUE.front()};
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
            threadArgs[i] = {i, &ram, &Cache,&READY_QUEUE.front(),static_cast<int>(Bilhetes.size())};
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
            threadArgs[i] = {i, &ram,&Cache,&READY_QUEUE.front()};
            if (pthread_create(&threads[i], nullptr, CoreFunction_SJF, (void*)&threadArgs[i]) != 0) {
                std::cerr << "Erro ao criar a thread " << i << std::endl;
                return 1;
            }
            if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
            if(!PRIORITY_READY_QUEUE.empty()){PRIORITY_READY_QUEUE.pop();}
        }

        for (int i = 0; i < (argc-2); i++){
            pthread_join(threads[i], nullptr);
        }
    }


    return 0;
}
