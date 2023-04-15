#include "Edge.h"

Edge::Edge(){};
Edge::~Edge(){};
void Edge::setAnt(Edge *p)
{
    ant = p;
};
void Edge::setProx(Edge *p)
{
    prox = p;
};
void Edge::setInfo(int val)
{
    info = val;
};
Edge *Edge::getAnt()
{
    return ant;
};
Edge *Edge::getProx()
{
    return prox;
};
int Edge::getInfo()
{
    return info;
};