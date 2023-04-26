#include "Node.h"

Node::Node(){
    this->primeiraAresta = nullptr;
    this->proxNo = nullptr;
}

Node::Node(int id)
{
    this->id = id;

    // colocando valores para grau de entrada e saída caso digrafo
    this->grauNo = 0;
    //TODO: aqui poderia ser bom receber uma informação se é digrafo ou n pra sabermos se vamos inicializar 
    // grauNo ou grauEntradaNo/grauSaidaNo
    // this->grauEntradaNo = 0;
    // this->grauSaidaNo = 0;

    this->primeiraAresta = nullptr;
    this->proxNo = nullptr;
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

Edge* Node::getPrimeiraAresta(){
    return this->primeiraAresta;
}

void Node::insereAresta(int idCauda, int idCabeca, float peso){
    Edge* novaAresta = new Edge(idCauda, idCabeca, peso);

    if(this->primeiraAresta == nullptr){ //Primeira aresta
        this->primeiraAresta = novaAresta;
    }else{
        Edge* aux = this->primeiraAresta;

        while (aux->getProxAresta() != nullptr) //Encontra a última aresta
        {
            aux = aux->getProxAresta();
        }
        
        aux->setProxAresta(novaAresta); //seta a proxima aresta da atual ultima aresta para a nova aresta inserida
    }
}

int Node::getGrauNo()
{
    return this->grauNo;
}