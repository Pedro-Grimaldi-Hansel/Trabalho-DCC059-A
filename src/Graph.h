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
        Graph(bool digrafo);
        ~Graph();
};

#endif // GRAPH_H_INCLUDED