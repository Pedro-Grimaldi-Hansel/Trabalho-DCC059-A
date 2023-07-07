#include <iostream>
#include <fstream>
#include <set>
#include <chrono>

#include "src/Graph.h"

using namespace std;
using namespace chrono;

int main(int argc, char const *argv[])
{
     // Verificando os parâmetros do programa
    if (argc != 6) 
    {
        cout << "ERRO: Esperado: ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida> <direcionado[0,1]> <ponderadoAresta[0,1]> <ponderadoVertice[0,1]>" << endl;
        return 1;
    }

    ifstream arquivoEntrada;
    ofstream arquivoSaida;
    // Criando o Grafo com base na Instância selecionada em .vscode/settings.json
    arquivoEntrada.open(argv[1], ios::in);
    arquivoSaida.open(argv[2], ios::out | ios::trunc);
    bool digrafo = string(argv[3]) != "0";
    bool ponderadoAresta =  string(argv[4]) != "0";
    bool ponderadoVertice = string(argv[5]) != "0";
    Graph* grafo = new Graph(arquivoEntrada);

    cout << "**************************************" << endl;
    cout << "Qual função deseja executar?" << endl;
    cout << "**************************************" << endl;
    cout << "a) Vizinhança Aberta" << endl;
    cout << "b) Vizinhança Fechada" << endl;
    cout << "c) Verificar se o Grafo é Bipartido" << endl;
    cout << "d) Fecho Transitivo Direto" << endl;
    cout << "e) Fecho Transitivo Indireto" << endl;
    cout << "f) Subgrafo Induzido" << endl;
    cout << "g) Componentes Fortemente Conexas (Digrafos)" << endl;
    cout << "h) Verificar se o grafo é Euleriano" << endl;
    cout << "i) Nós de Articulação" << endl;
    cout << "j) Arestas Ponte" << endl;
    cout << "k) Raio, Diâmetro, Centro e Periferia" << endl;
    cout << "l) AGM/Florestas" << endl;
    cout << "m) Caminho Mínimo" << endl;
    cout << "n) COBERTURA DE VÉRTICES - ALGORITMO GULOSO" << endl;
    cout << "o) COBERTURA DE VÉRTICES - ALGORITMO RANDOMIZADO" << endl;
    cout << "p) COBERTURA DE VÉRTICES - ALGORITMO RANDOMIZADO REATIVO" << endl;
    cout << "q) Sair do programa" << endl;

    char option;
    cin >> option;

    while(option != 'q')
    {
        switch(option)
        {
            case 'a':
            {
                int param;
                cout << "________________" << endl;
                cout << "Digite o ID do vértice de intresse:" << endl;
                cin >> param;
                cout << "Resultado:" << endl;
                grafo->vizinhancaAberta(param);
                cout << "________________" << endl;
                break;
            }
            case 'b':
            {
                int param;
                cout << "________________" << endl;
                cout << "Digite o ID do vértice de intresse:" << endl;
                cin >> param;
                cout << "Resultado:" << endl;
                grafo->vizinhancaFechada(param);
                cout << "________________" << endl;
                break;
            }
            case 'c':
            {
                cout << "________________" << endl;
                if(grafo->isBipartide())
                {
                    cout << "Sim, o grafo é bipartido!" << endl;
                }
                else
                {
                    cout << "Não, o grafo não é bipartido!" << endl;
                }
                cout << "________________" << endl;
            }
            case 'd':
            {
                cout << "________________" << endl;

                cout << "________________" << endl;
            }
            case 'e':
            {

            }
            case 'f':
            {

            }
            case 'g':
            {
                cout << "________________" << endl;
                grafo->stronglyConnectedComponents();
                cout << "________________" << endl;
            }
            case 'h':
            {
                cout << "________________" << endl;
                if(grafo->isEulerian())
                {
                    cout << "Sim, o grafo é euleriano!" << endl;
                }
                else
                {
                    cout << "Não, o grafo não é euleriano!" << endl;
                }
                cout << "________________" << endl;
            }
            case 'i':
            {
                set<int> articulationNodes = grafo->findArticulationNodes();
                cout << "________________" << endl;
                for (int node : articulationNodes) 
                {
                    cout << node << " ";
                }
                cout << "\n";
                cout << "________________" << endl;
            }
            case 'j':
            {
                vector<Edge*> bridges = grafo->findBridges();
                cout << "________________" << endl;
                for(int i = 0; i < bridges.size(); i++)
                {
                    cout << "Aresta: " << bridges[i]->getIdCabeca() << ", " << bridges[i]->getIdCauda() << endl;
                }
                cout << "________________" << endl;
            }
            case 'k':
            {
                
            }
            case 'l':
            {
                
            }
            case 'm':
            {
                
            }
            case 'n':
            {
                
            }
            case 'o':
            {
                
            }
            case 'p':
            {
                
            }
            default:
            {
                cout << "Insira uma opção válida" << endl;
            }
        }
    }
    
    return 0;
}