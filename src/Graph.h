#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"

using namespace std;

class Graph{
    private:
        Node* primeiroNo;
        Node* ultimoNo;
        bool digrafo;
        void imprimeInvertidoAux(Node* no);
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

        void imprime();
        void imprimeInvertido();

};

#endif // GRAPH_H_INCLUDED