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
    arquivoSaida.open(argv[2], ios::out | ios::app);
    bool digrafo = string(argv[3]) != "0";
    bool ponderadoAresta =  string(argv[4]) != "0";
    bool ponderadoVertice = string(argv[5]) != "0";

    Graph* grafo = new Graph(arquivoEntrada);
    float time = 0;
    Solution sol;
    float alpha[] = {0.05, 0.10, 0.15, 0.30, 0.50};
    sol = grafo->coberturaMinimaGulosaRandomizadaReativa(alpha, 5, 5000, 500);
    arquivoSaida << "====================================================" << endl;
    arquivoSaida << "Solução Gulosa Randomizada Reativa: " << endl;
    arquivoSaida << "Custo total: " << sol.getCustoTotal() << endl;
    arquivoSaida << "Tempo de execução: " << sol.getTempoExecucao() << endl;
    arquivoSaida << "Alpha: " << sol.getAlpha() << endl;
    arquivoSaida << "====================================================" << endl;
        
   
    return 0;
}