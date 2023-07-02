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
    arquivoSaida << "===============================================" << endl;
    arquivoSaida << "Para o arquivo: " << argv[1] << endl;

    Solution sol = grafo->coberturaMinimaGulosa();

    arquivoSaida << "- Solução Gulosa: " << endl;
    arquivoSaida << "\tCusto: " << sol.getCustoTotal() << ", Tempo: " << sol.getTempoExecucao() << " segundos" << endl;

    int numeroExecRandomizado = 10;
    float alpha[] =  {0.05, 0.1, 0.15, 0.3, 0.5};
    int tamAlpha = 5;

    float tempoAcumulado = 0;
    float custoAcumulado = 0;

    for(int j = 0; j < tamAlpha; j++){
        for(int i = 0; i < numeroExecRandomizado; i++){
            sol = grafo->coberturaMinimaGulosaRandomizada(alpha[j], 1000);
            tempoAcumulado += sol.getTempoExecucao();
            custoAcumulado += sol.getCustoTotal();
        }

        arquivoSaida << endl << "- Solução Gulosa Randomizada para o alpha " << alpha[j] << ": " << endl;
        arquivoSaida << "\tMédia do Custo: " << custoAcumulado/numeroExecRandomizado;
        arquivoSaida << ", Média do Tempo: " << tempoAcumulado/numeroExecRandomizado << " segundos" << endl;
    }

    int numeroExecReativo = 10;

    arquivoSaida << endl << "- Solução Gulosa Randomizada Reativa: " << endl;
    arquivoSaida << "Resultados: "<< endl;
    for(int i = 0; i < numeroExecReativo; i++){
        high_resolution_clock::time_point start = high_resolution_clock::now();
        double time = 0;

        sol = grafo->coberturaMinimaGulosaRandomizadaReativa(alpha, tamAlpha, 5000, 500);

        high_resolution_clock::time_point stop = high_resolution_clock::now();
        time = duration_cast<duration<double>>(stop - start).count();

        arquivoSaida << "\t" <<  i+1 << ") Custo: " << sol.getCustoTotal() << ", Tempo: " << time << ", alpha: " << sol.getAlpha() << endl;
    }
    
    return 0;
}