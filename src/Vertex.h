#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include "VertexList.h"

class Vertex
{
public:
    Vertex();
    ~Vertex();
    void setAnt(Vertex *p);
    void setProx(Vertex *p);
    void setId(int val);
    Vertex* getAnt();
    Vertex* getProx();
    int getId();
private:
    Vertex *ant; // ponteiro para anterior
    int id; // id
    Vertex *prox; // ponteiro para proximo
    VertexList *relatedVertices;
};

#endif // VERTEX_H_INCLUDED
