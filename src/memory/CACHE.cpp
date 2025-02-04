#include"CACHE.h"

void Cache_Memory::adicionarCache(const string& instrucao, const string& operandos, int32_t resultado){
    if (cache.find(instrucao) == cache.end()) {
        if (cache.size() >= 5) {
            string mais_antiga = ordem_insercao.front();
            cache.erase(mais_antiga);
            ordem_insercao.pop_front();
        }
        ordem_insercao.push_back(instrucao);
        cache[instrucao] = deque<Entrada>();
    }

    if (cache[instrucao].size() >= 5) {
        cache[instrucao].pop_front();
    }

    cache[instrucao].push_back(Entrada(operandos, resultado));
}

bool Cache_Memory::buscarNaCache(const string& instrucao, const string& operandos){
    auto it_instrucao = cache.find(instrucao);
    if (it_instrucao == cache.end()) {
        return false;
    }

    for (const auto& entrada : it_instrucao->second) {
        if (entrada.operandos == operandos) {
            return true;
        }
    }
    
    return false;
}

int32_t Cache_Memory::buscarResultado(const string& instrucao, const string& operandos){
    auto it_instrucao = cache.find(instrucao);
    if (it_instrucao == cache.end()) {
        return 0; 
    }

    for (const auto& entrada : it_instrucao->second) {
        if (entrada.operandos == operandos) {
            return entrada.resultado; 
        }
    }
    return 0;
}