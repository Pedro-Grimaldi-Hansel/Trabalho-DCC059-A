#include "Edge.h"

Edge::Edge(int idCabeca, float peso){
    this->idCabeca = idCabeca;
    this->idCauda = idCauda;
    this->peso = peso;
    this->proxAresta = nullptr;
}

Edge::~Edge()
{
}

float Edge::getPeso(){
    return this->peso;
}

void Edge::setPeso(float peso) {
    this->peso = peso;
}

int Edge::getIdCabeca(){
    return this->idCabeca;
}

void Edge::setIdCabeca(int idCabeca) {
    this->idCabeca = idCabeca;
}

int Edge::getIdCauda(){
    return this->idCauda;
}

void Edge::setIdCauda(int idCauda) {
    this->idCauda = idCauda;
}

Edge* Edge::getProxAresta(){
    return this->proxAresta;
}
void Edge::setProxAresta(Edge* aresta){
    this->proxAresta = aresta;
}