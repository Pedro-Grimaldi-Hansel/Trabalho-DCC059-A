#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"

using namespace std;

class Graph{
    private:
        Node* primeiroNo;
        Node* ultimoNo;
        bool digrafo;
    public:
        //Construtor e destrutor
        Graph(bool digrafo);
        ~Graph();

        //Inserção de Nos
        void insereNoInicio(int id);
        void insereNoFim(int id);
        Node* buscaNo(int id);

        //Inserção de arestas
        void insereAresta(int idCauda, int idCabeca, float peso);

        //Remoção de aresta
        void removeAresta(int idCauda, int idCabeca);

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


};

#endif // GRAPH_H_INCLUDED