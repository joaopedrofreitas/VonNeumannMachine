#include"cpu/Core.cpp"
#include <pthread.h>

float calculateSimilarity(const vector<string>& instr1, const vector<string>& instr2);
vector<vector<float>> createSimilarityMatrix(const vector<vector<string>>& instructionSet);
void sortBySimilarity(vector<PCB>& processes, const vector<vector<float>>& similarityMatrix);
void printReadyQueueWithAvg(queue<PCB>& readyQueue, const vector<vector<float>>& similarityMatrix);


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
    vector<vector<string>> Instruction_set;
    Instruction_set.resize((argc-2));
    vector<PCB> processes;
    vector<PCB> processList;

    for (int i = 0; i < (argc-2); i++) {

        PCB processo = loadProgram(argv[i + 1], ram, i, LAST_ADDRESS, WAITING_QUEUE[2], PERMISSIONS[2], Instruction_set[i]);

        for(int i=Bilhetes.size(); i < (LAST_ADDRESS/3);i++){
            processo.Tickets.push_back(i);
            Bilhetes.push_back(i);
        }
        READY_QUEUE.push(processo);
        PRIORITY_READY_QUEUE.push(processo); // SJF
    }
    while (!READY_QUEUE.empty()) {
        processes.push_back(std::move(READY_QUEUE.front()));
        READY_QUEUE.pop();
    }
    
    auto similarityMatrix = createSimilarityMatrix(Instruction_set);
    sortBySimilarity(processes, similarityMatrix);

    for(auto& p : processes) {
        READY_QUEUE.push(move(p));
    }

    printReadyQueueWithAvg(READY_QUEUE, similarityMatrix);

    if(argv[argc-1][0] == '0'){     //FIFO
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
    else if(argv[argc-1][0]== '1'){     //LOTERIA
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
    else if(argv[argc-1][0]== '2'){     //SJF

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
    else if(argv[argc-1][0] == '3') {  //SJF Com Fila de binários
        for (int i = 0; i < (argc-2); i++) {
            threadArgs[i] = {i, &ram, &Cache, &READY_QUEUE.front()};
            if (pthread_create(&threads[i], nullptr, CoreFunction_SJF_Binary, (void*)&threadArgs[i]) != 0) {
                std::cerr << "Erro ao criar thread " << i << std::endl;
                return 1;
            }
            if(!READY_QUEUE.empty()){READY_QUEUE.pop();}
            if(!BINARY_READY_QUEUE.empty()){ BINARY_READY_QUEUE.pop(); }
        }
        
        for (int i = 0; i < (argc-2); i++){
            pthread_join(threads[i], nullptr);
        }
    }


    return 0;
}



float calculateSimilarity(const vector<string>& instr1, const vector<string>& instr2) {
    size_t total = max(instr1.size(), instr2.size());
    if(total == 0) return 0.0f;
    
    size_t matches = 0;
    for(size_t i = 0; i < min(instr1.size(), instr2.size()); ++i) {
        if(instr1[i] == instr2[i]) {
            ++matches;
        }
    }
    return (static_cast<float>(matches) / total) * 100.0f;
}

vector<vector<float>> createSimilarityMatrix(const vector<vector<string>>& instructionSet) {
    const size_t n = instructionSet.size();
    vector<vector<float>> matrix(n, vector<float>(n, 0.0f));
    
    #pragma omp parallel for collapse(2)
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            if(i != j) {
                matrix[i][j] = calculateSimilarity(instructionSet[i], instructionSet[j]);
            }
        }
    }
    return matrix;
}

void sortBySimilarity(vector<PCB>& processes, const vector<vector<float>>& similarityMatrix) {
    vector<pair<float, size_t>> avgSimilarities;
    
    for(size_t i = 0; i < processes.size(); ++i) {
        float total = 0.0f;
        int count = 0;
        for(size_t j = 0; j < processes.size(); ++j) {
            if(i != j) {
                total += similarityMatrix[i][j];
                ++count;
            }
        }
        avgSimilarities.emplace_back(total/count, i);
    }
    
    sort(avgSimilarities.begin(), avgSimilarities.end(), 
        [](const pair<float, size_t>& a, const pair<float, size_t>& b) {
            return a.first > b.first;
        });
    
    vector<PCB> sortedProcesses;
    for(const auto& p : avgSimilarities) {
        sortedProcesses.push_back(move(processes[p.second]));
    }
    
    processes = move(sortedProcesses);
}

void printReadyQueueWithAvg(queue<PCB>& readyQueue, const vector<vector<float>>& similarityMatrix) {
    queue<PCB> tempQueue = readyQueue;
    size_t index = 0;

    cout << "READY_QUEUE ordenada por similaridade média:\n";
    cout << "--------------------------------------------\n";
    
    while (!tempQueue.empty()) {
        PCB currentProcess = tempQueue.front();
        tempQueue.pop();

        float totalSimilarity = 0.0f;
        int count = 0;
        for (size_t i = 0; i < similarityMatrix.size(); ++i) {
            if (index != i) { 
                totalSimilarity += similarityMatrix[index][i];
                ++count;
            }
        }
        float avgSimilarity = (count > 0) ? (totalSimilarity / count) : 0.0f;

        cout << "Processo " << currentProcess.process_id 
             << " (média: " << fixed << setprecision(2) << avgSimilarity << "%)\n";

        ++index;
    }
    cout << "--------------------------------------------\n";
}
