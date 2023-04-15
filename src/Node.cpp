#include "Node.h"

Node::Node(Edge* primeiraAresta, int id, Node* proxNo)
{
    this->primeiraAresta = primeiraAresta;
    this->id = id;
    this->proxNo = proxNo;
}

Node::~Node()
{
}