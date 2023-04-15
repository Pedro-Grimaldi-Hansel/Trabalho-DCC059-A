#include <iostream>
#include <fstream>
#include "src/Graph.h"

using namespace std;

Graph* lerArquivo(ifstream &arquivoEntrada){
    //Pegar primeira linha e ver o número de nos
    int ordemGrafo;
    int idCauda;
    int idCabeca;
    float peso;

    arquivoEntrada >> ordemGrafo;
    cout << "A ordem do grafo é: " << ordemGrafo << endl;

    //Pegar linha até o fim do arquivo
    while( arquivoEntrada >> idCauda >> idCabeca >> peso) {
        
    }

    return NULL;
}

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

    if(arquivoEntrada.is_open()){
        Graph* grafo = lerArquivo(arquivoEntrada);
    }

    return 0;
}