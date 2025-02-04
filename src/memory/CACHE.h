#ifndef CACHE_H
#define CACHE_H

#include "MEMORYCELL.h"
#include "stdbool.h"
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>
#include <map>
#include <cstdint>
#include <optional>
#include <cstring>

using namespace std;

struct Entrada {
    string operandos;
    int32_t resultado;

    Entrada(const string& op, int32_t res) 
        : operandos(op), resultado(res) {}
};

struct Cache_Memory{
    map<string, deque<Entrada>> cache;
    deque<string> ordem_insercao;

    void adicionarCache(const string& instrucao, const string& operandos, int32_t resultado);
    bool buscarNaCache(const string& instrucao, const string& operandos);
    int32_t buscarResultado(const string& instrucao, const string& operandos);

    void PrintCache(){
        for (const auto& instrucao : ordem_insercao) {
            auto& lista = cache[instrucao];
            cout << "Instrução: " << instrucao << endl;
            
            for (const auto& entrada : lista) {
                cout << "  Operandos: " << entrada.operandos 
                    << " => Resultado: " << entrada.resultado << endl;
            }
        }
    }


};

#endif