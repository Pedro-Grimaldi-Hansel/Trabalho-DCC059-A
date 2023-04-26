#include "Edge.h"

Edge::Edge(int idCauda,int idCabeca, float peso){
    this->idCauda = idCauda;
    this->idCabeca = idCabeca;
    this->peso = peso;
    this->proxAresta = nullptr;
}

Edge::Edge(Edge* proxAresta, float peso, int idCauda, int idCabeca)
{
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

int Edge::getIdCauda(){
    return idCauda;
}

void Edge::setIdCauda(int idCauda) {
    this->idCauda = idCauda;
}

int Edge::getIdCabeca(){
    return this->idCabeca;
}

void Edge::setIdCabeca(int idCabeca) {
    this->idCabeca = idCabeca;
}

Edge* Edge::getProxAresta(){
    return this->proxAresta;
}
void Edge::setProxAresta(Edge* aresta){
    this->proxAresta = aresta;
}