#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <fstream>
#include"Solution.h"
#include "Node.h"
#include <vector>


using namespace std;

class Graph{
    private:
        Node* primeiroNo;
        Node* ultimoNo;
        bool digrafo;
        bool pesoNasArestas;
        bool pesoNosVertices;
        int numArestas;


        int ultimoIdVinculado;
        Node* ultimoNoVinculado;

        vector< Edge > OrdenaArestas(vector< Edge > arestas, int numArestas);
        void quickSort(vector< Edge >& arestas, int low, int high);

        void imprimeAGM(vector< Edge > AGM, int subarvores[], int mapa[], int numNos);
        void atualizaSubarvores(int numNos, int subarvores[], int indiceCabecaSubarvores, int indiceCaudaSubarvores);
        int buscaNoVector(vector< int > vector, int valor, int tam);
        int buscaNoVectorNos(vector< Node > vector, int valor, int tam);
        int buscaNoVetor(int vetor[], int idArquivo, int tam);
        void quickSortGuloso(std::vector<Node>& vetor, int low, int high);
        int partitionGuloso(std::vector<Node>& vetor, int low, int high);
        void swap(Node* a, Node* b);
        void inicializaVetores(vector<float>& probabilidades, vector<float>& medias, vector<int>& aparicoes, int m);
        void atualizaProbabilidades(vector<float>& probabilidades, vector<float> medias, float* alpha, Solution solBest);
        int escolheAlfa(vector<float> probabilidades);
        void atualizaMedias(vector<float>& medias, vector<int> aparicoes, int indiceEscolhido, Solution sol );

    public:
        //Destrutor
        ~Graph();

        //Leitura de arquivo
        Graph(ifstream &arquivoEntrada, bool digrafo, bool ponderadoVertice, bool ponderadoAresta);
        
        //Leitura somente para o trabalho
        Graph(ifstream &arquivoEntrada);

        //Escrita no arquivo
        void escreveArquivo(ofstream &arquivoSaida);
        void escreveArquivoDOT(ofstream &arquivoSaida);

        //Inserção de Nos
        void vinculaNo(int idArquivo);
        void insereNoFim(int id);
        void insereNoFim(int id, int idArquivo);
        Node* buscaNoPorIdArquivo(int idArquivo);

        //Inserção de arestas
        void insereAresta(int idCauda, int idCabeca, float peso);
        void insereArestaTrabalho(int idCauda, int idCabeca);

        //Remoção de aresta
        void removeAresta(int idCauda, int idCabeca);

        //Remoção de nó
        bool removeNo(int idArquivo);

        void imprime();

        bool getDigrafo();

        int getGrauNo(int id); // retorna o grau de um nó se n for digrafo
        int getEntradaNo(int id); // retirna grau de entrada se for digrafo
        int getSaidaNo(int id); // retirna grau de saída se for digrafo
        Node* getPrimeiroNo(); // retorna o primeiro nó do grafo

        int getNumArestas();
        void setNumArestas(int numArestas);


        bool getKRegularidade(int k); // retorna true se todos os vértices possuem grau k, else do contrário

        int getOrdem();

        bool isTrivial(); // retorna true se o grafo possui apenas 1 nó 
        bool isNulo(); // retorna true se o grafo não possui nenhum nó

        int getGrauGrafo();

        int* sequenciaDeGraus(); //Apresentar a sequência de graus do grafo.
        void vizinhancaAberta(int id);
        void vizinhancaFechada(int id);

        void AGM();
       
        void coberturaMinimaGulosa();
        Solution coberturaMinimaGulosaRandomizada(float alpha, int nInteracoes);
        void coberturaMinimaGulosaRandomizadaReativa(float* alpha, int tammanhoVetor, int nIterecoes, int bloco);

        bool verificaSolucao(vector< int >solucao);

};

#endif // GRAPH_H_INCLUDED