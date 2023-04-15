#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include "Vertex.h"

class Edge
{
public:
    Edge();
    ~Edge();
    void setAnt(Edge *p);
    void setProx(Edge *p);
    void setPeso(int val);
    Edge* getAnt();
    Edge* getProx();
    int getPeso();
private:
    Edge *ant; // ponteiro para anterior
    Edge *prox; // ponteiro para proximo
    int peso; // informacao
    Vertex *cauda;
    Vertex *cabeca;

};

#endif // EDGE_H_INCLUDED
