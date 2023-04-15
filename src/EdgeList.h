#ifndef EDGELIST_H_INCLUDED
#define EDGELIST_H_INCLUDED
#include "Edge.h"

class EdgeList
{
public:
    EdgeList();
    ~EdgeList();
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
    Edge *primeiro;
    int n;
    Edge *ultimo;
    void removeNo(Edge *p);
};

#endif // EDGELIST_H_INCLUDED
