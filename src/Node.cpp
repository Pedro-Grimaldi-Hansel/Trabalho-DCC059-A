#include "Node.h"

Node::Node(){
    this->primeiraAresta = nullptr;
    this->proxNo = nullptr;
}

Node::Node(int idAplicacao)
{
    this->idAplicacao = idAplicacao;

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
    Edge* aux = this->primeiraAresta;
    Edge* arestaASerDeletada;
    if( aux != nullptr)
    {
        while(aux->getProxAresta() != nullptr){
            arestaASerDeletada = aux;
            aux = aux->getProxAresta();
            delete arestaASerDeletada;
        }
    }
}

void Node::setProxNo(Node* proximo)
{
    this->proxNo = proximo;
}

Node* Node::getProxNo()
{
    return this->proxNo;
}

Edge* Node::getPrimeiraAresta(){
    return this->primeiraAresta;
}

void Node::insereAresta(int idCabeca, float peso){
    Edge* novaAresta = new Edge(idCabeca, peso);

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

Edge* Node::buscaAresta(int idCabeca){
    Edge* edge = this->primeiraAresta;

    if(this->primeiraAresta == nullptr){
        //Nó isolado
        return nullptr;
    }

    //Percorre todas as arestas
    while(edge != nullptr){
        if(edge->getIdCabeca() == idCabeca){
            break; //encontrou a aresta
        }
        edge = edge->getProxAresta();
    }

    //Aresta não encontrada
    if(edge == nullptr){
        return nullptr;
    }

    return edge;
}

bool Node::removeAresta(int idCabeca){
    Edge* aresta = this->primeiraAresta;
    Edge* arestaAnteriror = nullptr;

    if(this->primeiraAresta == nullptr){
        cout << "Aresta inexistente" << endl;
        return false;
    }

    //Percorre todas as arestas armazenando a atual e anterior
    while(aresta != nullptr){
        if(aresta->getIdCabeca() == idCabeca){
            break; //encontrou a aresta
        }
        arestaAnteriror = aresta;
        aresta = aresta->getProxAresta();
    }

    //Aresta não encontrada
    if(aresta == nullptr){
        cout << "Aresta não encotrada!" << endl;
        return false;
    }

    if(arestaAnteriror == nullptr){
        //a aresta é a primeira da lista
        this->primeiraAresta = aresta->getProxAresta();
    }else if(aresta->getProxAresta() == nullptr){
        //a aresta é a ultima da lista
        arestaAnteriror->setProxAresta(nullptr);
    }else{
        //a aresta está no meio
        arestaAnteriror->setProxAresta(aresta->getProxAresta());
    }
    
    delete aresta;
    return true;
}

int Node::getIdArquivo()
{
    return this->idArquivo;
}

int Node::getGrauNo()
{
    return this->grauNo;
}

int Node::getEntradaNo()
{
    return this->grauEntradaNo;
}

int Node::getSaidaNo()
{
    return this->grauSaidaNo;
}

float Node::getPesoNo()
{
    return this->peso;
}

void Node::setIdArquivo(int idArquivo)
{
    this->idArquivo = idArquivo;
}

void Node::setGrauNo(int grau)
{
    this->grauNo = grau;
}

void Node::setEntradaNo(int grau)
{
    this->grauEntradaNo = grau;
}

void Node::setSaidaNo(int grau)
{
    this->grauSaidaNo = grau;
}

void Node::setPesoNo(float peso)
{
    this->peso = peso;
}