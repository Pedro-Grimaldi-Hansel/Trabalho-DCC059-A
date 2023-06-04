#include <iostream>
#include <fstream>
#include "src/Graph.h"

using namespace std;

int main(int argc, char const *argv[]){
     // Verificando os parâmetros do programa
    if (argc != 3) 
    {
        cout << "ERRO: Esperado: ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida>" << endl;
        return 1;
    }

    ifstream arquivoEntrada;
    ofstream arquivoSaida;

    arquivoEntrada.open(argv[1], ios::in);
    arquivoSaida.open(argv[2], ios::out | ios::trunc);
    bool digrafo = false;
    Graph* grafo = new Graph(arquivoEntrada);
  
    grafo->imprime();
    grafo->AGM();

    // cout << retorno << endl;

    return 0;
}