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

    Solution sol = grafo->coberturaMinimaGulosaRandomizada(0.1, 1000);
    cout << "Solução: " << sol.getCustoTotal() << ", Tempo: " << sol.getTempoExecucao() << ", Tam: " << sol.getSolucao().size() << endl;
    // float alpha[] = {0.1, 0.3, 0.25, 0.60, 0.75};
    // grafo->coberturaMinimaGulosaRandomizadaReativa(alpha, 5, 1000, 10);
   
    return 0;
}