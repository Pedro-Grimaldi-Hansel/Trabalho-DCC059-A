#include "Node.h"

Node::Node(){}

Node::Node(int id)
{
    this->id = id;
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
