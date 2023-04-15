#include <iostream>
#include "EdgeList.h"

using namespace std;

void EdgeList::removeNo(Edge *p)
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
       Edge* ant = p->getAnt();
       Edge* prox = p->getProx();

       ant->setProx(prox);
       prox->setAnt(ant);

       delete p;
       n = n - 1;
    }
}

EdgeList::EdgeList()
{
    primeiro = ultimo = NULL;
    n = 0;
}

EdgeList::~EdgeList()
{
    Edge *p = primeiro;
    while(p != NULL)
    {
        Edge *t = p->getProx();
        delete p;
        p = t;
    }
}

bool EdgeList::busca(int val)
{
    for(Edge *p = primeiro; p != NULL; p = p->getProx())
        if(p->getInfo() == val)
            return true;
    return false;
}

void EdgeList::imprime()
{
    cout << "Lista: ";
    for(Edge *p = primeiro; p != NULL; p = p->getProx())
        cout << p->getInfo() << " ";
    cout << endl;
}

void EdgeList::imprimeReverso()
{
    cout << "Lista Reversa: ";
    for(Edge *p = ultimo; p != NULL; p = p->getAnt())
        cout << p->getInfo() << " ";
    cout << endl;
}

void EdgeList::insereInicio(int val)
{
    Edge *p = new Edge();
    p->setInfo(val);
    p->setAnt(NULL);
    p->setProx(primeiro);
    if(primeiro == NULL)
        ultimo = p;
    else
        primeiro->setAnt(p);
    primeiro = p;
    n++;
}

void EdgeList::insereFinal(int val)
{
    Edge *p = new Edge();
    p->setInfo(val);
    p->setProx(NULL);
    p->setAnt(ultimo);
    if(primeiro == NULL)
        primeiro = p;
    else
        ultimo->setProx(p);
    ultimo = p;
    n++;
}

void EdgeList::removeInicio()
{
    Edge *p;
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

void EdgeList::removeFinal()
{
    Edge *p;
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
bool EdgeList::removeNoVal(int val)
{
    bool removeu = false;
    Edge* p = primeiro;
    while( p != NULL )
    {
        if(p->getInfo() == val)
        {
            Edge* t = p->getProx();
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
