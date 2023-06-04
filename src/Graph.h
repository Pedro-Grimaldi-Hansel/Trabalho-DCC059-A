#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <fstream>
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

        int ultimoIdVinculado;
        Node* ultimoNoVinculado;

        vector< Edge > OrdenaArestas(vector< Edge > arestas, int numArestas);
        void quickSort(vector< Edge >& arestas, int low, int high);

        void imprimeAGM(vector< Edge > AGM, int subarvores[], int mapa[], int numNos);
        void atualizaSubarvores(int numNos, int subarvores[], int indiceCabecaSubarvores, int indiceCaudaSubarvores);
        int buscaNoVector(vector< int > vector, int valor, int tam);
        int buscaNoVetor(int vetor[], int idArquivo, int tam);

    public:
        //Construtor e destrutor
        ~Graph();

        //Leitura de arquivo
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


        bool getKRegularidade(int k); // retorna true se todos os vértices possuem grau k, else do contrário

        int getOrdem();

        bool isTrivial(); // retorna true se o grafo possui apenas 1 nó 
        bool isNulo(); // retorna true se o grafo não possui nenhum nó

        int getGrauGrafo();

        int* sequenciaDeGraus(); //Apresentar a sequência de graus do grafo.
        void vizinhancaAberta(int id);
        void vizinhancaFechada(int id);

        void AGM();
       

};

#endif // GRAPH_H_INCLUDED