#include <iostream>
#include <fstream>
#include <chrono>

#include "src/Graph.h"

using namespace std;
using namespace chrono;

int main(int argc, char const *argv[]){
     // Verificando os parâmetros do programa
    if (argc != 6) 
    {
        cout << "ERRO: Esperado: ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida> <direcionado[0,1]> <ponderadoAresta[0,1]> <ponderadoVertice[0,1]>" << endl;
        return 1;
    }

    ifstream arquivoEntrada;
    ofstream arquivoSaida;

    arquivoEntrada.open(argv[1], ios::in);
    arquivoSaida.open(argv[2], ios::out | ios::trunc);
    bool digrafo = string(argv[3]) != "0";
    bool ponderadoAresta =  string(argv[4]) != "0";
    bool ponderadoVertice = string(argv[5]) != "0";

    Graph* grafo = new Graph(arquivoEntrada);
    float time = 0;
    Solution sol;
    sol = grafo->coberturaMinimaGulosaRandomizada(0.1, 1000);
    cout << "====================================================" << endl;
    cout << "Solução Gulosa: " << endl;
    cout << "Tamanho da Solução: " << sol.getSolucao().size() << " vertices" << endl;
    cout << "Custo total: " << sol.getCustoTotal() << endl;
    cout << "Tempo de execução: " << sol.getTempoExecucao() << endl;
    cout << "====================================================" << endl;
        
   
    return 0;
}