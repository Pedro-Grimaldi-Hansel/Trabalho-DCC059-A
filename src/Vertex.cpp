#include "Vertex.h"

Vertex::Vertex(){};
Vertex::~Vertex(){};
void Vertex::setAnt(Vertex *p)
{
    ant = p;
};
void Vertex::setProx(Vertex *p)
{
    prox = p;
};
void Vertex::setId(int val)
{
    id = val;
};
Vertex *Vertex::getAnt()
{
    return ant;
};
Vertex *Vertex::getProx()
{
    return prox;
};
int Vertex::getId()
{
    return id;
};