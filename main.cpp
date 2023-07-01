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
    high_resolution_clock::time_point start = high_resolution_clock::now();
    grafo->coberturaMinimaGulosa();
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop - start).count();
    cout << "Tempo de execução: " << time << " segundos." << endl;
    // float alpha[] = {0.1, 0.3, 0.25, 0.60, 0.75};
    // grafo->coberturaMinimaGulosaRandomizadaReativa(alpha, 5, 1000, 10);
   
    return 0;
}