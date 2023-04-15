#include <iostream>
#include "VertexList.h"

using namespace std;

void VertexList::removeNo(Vertex *p)
//remove o n� da LDE apontado por p
{
    if( p == NULL )
        cout << "No p eh invalido!! " << endl;
    else if( primeiro == NULL )
        cout << "Lista vazia" << endl;
    else if (primeiro == ultimo ) //caso I
    {
        primeiro = ultimo = NULL;
        delete p;
        n = n - 1;
    }
    else if( p == primeiro ) //caso II
        removeInicio();
    else if( p == ultimo ) //caso III
        removeFinal();
    else // p aponta para um n� no meio da LDE. logo, n >=3
    {
       Vertex* ant = p->getAnt();
       Vertex* prox = p->getProx();

       ant->setProx(prox);
       prox->setAnt(ant);

       delete p;
       n = n - 1;
    }
}

VertexList::VertexList()
{
    primeiro = ultimo = NULL;
    n = 0;
}

VertexList::~VertexList()
{
    Vertex *p = primeiro;
    while(p != NULL)
    {
        Vertex *t = p->getProx();
        delete p;
        p = t;
    }
}

bool VertexList::busca(int val)
{
    for(Vertex *p = primeiro; p != NULL; p = p->getProx())
        if(p->getId() == val)
            return true;
    return false;
}

void VertexList::imprime()
{
    cout << "Lista: ";
    for(Vertex *p = primeiro; p != NULL; p = p->getProx())
        cout << p->getId() << " ";
    cout << endl;
}

void VertexList::imprimeReverso()
{
    cout << "Lista Reversa: ";
    for(Vertex *p = ultimo; p != NULL; p = p->getAnt())
        cout << p->getId() << " ";
    cout << endl;
}

void VertexList::insereInicio(int val)
{
    Vertex *p = new Vertex();
    p->setId(val);
    p->setAnt(NULL);
    p->setProx(primeiro);
    if(primeiro == NULL)
        ultimo = p;
    else
        primeiro->setAnt(p);
    primeiro = p;
    n++;
}

void VertexList::insereFinal(int val)
{
    Vertex *p = new Vertex();
    p->setId(val);
    p->setProx(NULL);
    p->setAnt(ultimo);
    if(primeiro == NULL)
        primeiro = p;
    else
        ultimo->setProx(p);
    ultimo = p;
    n++;
}

void VertexList::removeInicio()
{
    Vertex *p;
    if(primeiro != NULL)
    {
        p = primeiro;
        primeiro = p->getProx();
        delete p;
        if(primeiro == NULL)
            ultimo = NULL;
        else
            primeiro->setAnt(NULL);
        n--;
    }
    else
        cout << "ERRO: Lista vazia" << endl;
}

void VertexList::removeFinal()
{
    Vertex *p;
    if(primeiro != NULL)
    {
        p = ultimo;
        ultimo = p->getAnt();
        delete p;
        if(ultimo == NULL)
            primeiro = NULL;
        else
            ultimo->setProx(NULL);
        n--;
    }
    else
        cout << "ERRO: Lista vazia" << endl;
}
bool VertexList::removeNoVal(int val)
{
    bool removeu = false;
    Vertex* p = primeiro;
    while( p != NULL )
    {
        if(p->getId() == val)
        {
            Vertex* t = p->getProx();
            removeNo(p);
            p = t;
            removeu = true;
        }
        else
        {
            p = p->getProx();
        }
    }
    return removeu;
}


//Inser��o 4 ponteiros
//Remo��o 2 ponteiros
