#include <iostream>
#include <fstream>
#include <set>
#include <chrono>
#include <map>

#include "src/Graph.h"

using namespace std;
using namespace chrono;

void execAlgoritmo(Graph grafo, int algoritmoEscolhido, int numExecucoes, float alfa, int seed)
{
    Solution sol;
    if(algoritmoEscolhido == 1){
        sol = grafo.coberturaMinimaGulosa();
        cout << "Solução Algoritmo guloso" << endl;
        cout << "Peso: " << sol.getCustoTotal() << endl;
        cout << "Tempo: " << sol.getTempoExecucao() << " segundos" << endl;
        cout << "Tamanho: " << sol.getSolucao().size() << endl;
    }else if(algoritmoEscolhido == 2){
        sol = grafo.coberturaMinimaGulosaRandomizada(alfa, numExecucoes, seed);
        cout << "Algoritmo guloso randomizado adaptativo" << endl;
        cout << "Peso: " << sol.getCustoTotal() << endl;
        cout << "Tempo: " << sol.getTempoExecucao() << " segundos" << endl;
        cout << "Tamanho: " << sol.getSolucao().size() << endl;
        cout << "Alfa: " << alfa << endl;
    }else if(algoritmoEscolhido == 3){
        float alpha[] = {0.05, 0.10, 0.15, 0.30, 0.50};
        sol = grafo.coberturaMinimaGulosaRandomizadaReativa(alpha, 5, numExecucoes, (int) numExecucoes*0.1, seed);
        cout << "Algoritmo guloso randomizado adaptativo reativo" << endl;
        cout << "Peso: " << sol.getCustoTotal() << endl;
        cout << "Tempo: " << sol.getTempoExecucao() << " segundos" << endl;
        cout << "Tamanho: " << sol.getSolucao().size() << endl;
        cout << "Alfa: " << sol.getAlpha() << endl;
    }else{
        cout << "ALGORITMO INVÁLIDO! 1- Algoritmo guloso, 2- Algoritmo guloso randomizado adaptativo, 3- Algoritmo guloso randomizado adaptativo reativo" << endl;
    }

}

int main(int argc, char const *argv[])
{
     // Verificando os parâmetros do programa
    if (argc < 7) 
    {
        cout << "ERRO: Esperado: ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida> <direcionado[0,1]> <ponderadoAresta[0,1]> <ponderadoVertice[0,1]> <algoritmoEscolhido> <?numeroIterações> <?alfa> <?seed>" << endl;
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
    int algEscolhido = stoi(argv[6]);
    Graph* grafo = new Graph(arquivoEntrada);
    float alpha[] = {0.05, 0.10, 0.15, 0.30, 0.50};

    if(algEscolhido != 4){
        int numeroIteracoes = 1000;
        float alfa = 0.1;
        int seed = -1;

        if(algEscolhido != 1){
            numeroIteracoes = stoi(argv[7]);
            if(argc >= 8){
                alfa = stof(argv[8]);
                if(argc > 9){
                    seed = stoi(argv[9]);
                }
            }
        }
        execAlgoritmo(*grafo, algEscolhido, numeroIteracoes, alfa, seed);
        return 0;
    }

    char option = 'a';

    while(option != 'r')
    {
        cout << "\n";
        cout << "\n";
        cout << "\n";
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
        cout << "q) Escrever no arquivo" << endl;
        cout << "r) Sair do programa" << endl;
        cout << "\n";
        cout << "\n";
        cout << "\n";

        cin >> option;

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
                break;
            }
            case 'd':
            {
                int param;
                cout << "________________" << endl;
                cout << "Digite o ID do vértice de intresse:" << endl;
                cin >> param;
                cout << "Resultado:" << endl;
                grafo->fechoTransitivoDireto(param);
                cout << "________________" << endl;
                break;
            }
            case 'e':
            {
                int param;
                cout << "________________" << endl;
                cout << "Digite o ID do vértice de intresse:" << endl;
                cin >> param;
                cout << "Resultado:" << endl;
                grafo->fechoTransitivoIndireto(param);
                cout << "________________" << endl;
                break;
            }
            case 'f':
            {
                vector<int> nodes;
                int size;
                cout << "________________" << endl;
                cout << "Digite o tamanho do vetor de vértices: ";
                cin >> size;
                nodes.resize(size);
                cout << "Digite os vértices de interesse: ";
                for (int i = 0; i < size; i++) 
                {
                    cout << "Vértice " << i + 1 << ": ";
                    cin >> nodes[i];
                }
                cout << "Resultado:" << endl;
                grafo->subgrafoInduzido(nodes);
                cout << "________________" << endl;
                break;
            }
            case 'g':
            {
                cout << "________________" << endl;
                grafo->stronglyConnectedComponents();
                cout << "________________" << endl;
                break;
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
                break;
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
                break;
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
                break;
            }
            case 'k':
            {
                cout << "________________" << endl;
                grafo->raioDiametroCentroPeriferia();
                cout << "________________" << endl;
                break;
            }
            case 'l':
            {
                cout << "________________" << endl;
                grafo->AGM();
                cout << "________________" << endl;
                break;
            }
            case 'm':
            {
                int param;
                cout << "________________" << endl;
                cout << "Digite o ID do vértice de intresse:" << endl;
                cin >> param;
                cout << "Resultado:" << endl;
                grafo->caminhoMinimoDijkstra(param);
                cout << "________________" << endl;
                break;
            }
            case 'n':
            {
                cout << "Algoritmo Guloso" << endl;
                cout << "________________" << endl;
                Solution sol;
                sol = grafo->coberturaMinimaGulosa();
                cout << "====================================================" << endl;
                cout << "Solução Gulosa: " << sol.getSolucao().size() << endl;
                cout << "Custo total: " << sol.getCustoTotal() << endl;
                cout << "Tempo de execução: " << sol.getTempoExecucao() << " segundos" << endl;
                cout << "====================================================" << endl;
                cout << "________________" << endl;
                break;
            }
            case 'o':
            {
                cout << "Algoritmo Guloso Randomizado (1000 iterações)" << endl;
                cout << "________________" << endl;
                Solution sol;
                float alpha;
                cout << "Qual alfa você deseja?" << endl;
                cin >> alpha;
                sol = grafo->coberturaMinimaGulosaRandomizada(alpha, 1000, -1);
                cout << "====================================================" << endl;
                cout << "Solução Gulosa Randomizada: " << sol.getSolucao().size() << endl;
                cout << "Custo total: " << sol.getCustoTotal() << endl;
                cout << "Tempo de execução: " << sol.getTempoExecucao() << " segundos" << endl;
                cout << "====================================================" << endl;
                cout << "________________" << endl;
                break;
            }
            case 'p':
            {
                cout << "Algoritmo Guloso Randomizado Reativo (5000 iterações - Bloco 500)" << endl;
                cout << "________________" << endl;
                Solution sol;
                sol = grafo->coberturaMinimaGulosaRandomizadaReativa(alpha, 5, 5000, 500, -1);
                cout << "====================================================" << endl;
                cout << "Solução Gulosa Randomizada Reativa: " << sol.getSolucao().size() << endl;
                cout << "Custo total: " << sol.getCustoTotal() << endl;
                cout << "Tempo de execução: " << sol.getTempoExecucao() << " segundos" << endl;
                cout << "Alpha: " << sol.getAlpha() << endl;
                cout << "====================================================" << endl;
                cout << "________________" << endl;
                break;
            }
            case 'q':
            {
                cout << "________________" << endl;
                cout << "Escrevendo no arquivo..." << endl;
                grafo->escreveArquivo(arquivoSaida);
                cout << "________________" << endl;
                break;
            }
            case 'r':
            {
                cout << "________________" << endl;
                cout << "Adeus!" << endl;
                cout << "________________" << endl;
                break;
            }
            default:
            {
                cout << "Insira uma opção válida" << endl;
                break;
            }
        }
    }
    
    return 0;
}