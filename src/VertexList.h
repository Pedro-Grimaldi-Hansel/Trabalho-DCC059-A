#ifndef VERTEXLIST_H_INCLUDED
#define VERTEXLIST_H_INCLUDED
#include "Vertex.h"

class VertexList
{
public:
    VertexList();
    ~VertexList();
    bool busca(int val);
    void insereInicio(int val);
    void removeInicio();
    void insereFinal(int val);
    void removeFinal();
    void imprime();

    void imprimeReverso();
    bool removeNoVal(int val);
    int NumNO() { return n; };

private:
    Vertex *primeiro;
    int n;
    Vertex *ultimo;
    void removeNo(Vertex *p);
};

#endif // VERTEXLIST_H_INCLUDED
