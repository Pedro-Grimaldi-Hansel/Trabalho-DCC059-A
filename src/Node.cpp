#include "Node.h"

Node::Node(){}

Node::Node(int id)
{
    this->id = id;
    this->grauNo = 0;

    // colocando valores para grau de entrada e saída caso digrafo
    //TODO: aqui poderia ser bom receber uma informação se é digrafo ou n pra sabermos se vamos inicializar 
    // grauNo ou grauEntradaNo/grauSaidaNo
    // this->grauEntradaNo = 0;
    // this->grauSaidaNo = 0;
}

Node::~Node()
{
}

void Node::setProxNo(Node* proximo)
{
    this->proxNo = proximo;
}

Node* Node::getProxNo()
{
    return this->proxNo;
}

int Node::getId(){
    return this->id;
}

void Node::setId(int id){
    this->id = id;
}

void Node::insereAresta(int idCauda, int idCabeca, float peso){
    //TODO: implementar
}

int Node::getGrauNo()
{
    return this->grauNo;
}