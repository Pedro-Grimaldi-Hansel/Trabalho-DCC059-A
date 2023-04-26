#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(bool digrafo){
    this->digrafo = digrafo;
    this->primeiroNo = nullptr;
    this->ultimoNo = nullptr;
    this->ordem = 0;
}

void Graph::insereNoInicio(int id){
    Node* no = new Node(id); //Cria um nó com o valor passado por parametro

    no->setProxNo(this->primeiroNo); //preenche o próximo

    this->primeiroNo = no; //no passa a ser o primeiro do grafo
}

void Graph::insereNoFim(int id){
    Node* no = new Node(id);
    no->setProxNo(nullptr);

    if(this->primeiroNo == nullptr) //caso o grafo esteja vazio, insere no inicio mesmo
    {
        this->primeiroNo = this->ultimoNo = no;
    }
    else
    {
        this->ultimoNo->setProxNo(no);
        this->ultimoNo = no;
    }
}

Node* Graph::buscaNo(int id){
    Node* no = this->primeiroNo; //auxiliar para busca

    while (no != nullptr)
    {
        if(no->getId() == id){ //caso encontrou o nó retorna ele
            return no;
        }

        no = no->getProxNo(); //se não encontrou passa para o próximo
    }
    //caso nao tenha encontrado nenhum, retorna nullptr
    return nullptr;
}

void Graph::insereAresta(int idCauda, int idCabeca, float peso){
    Node* cauda = buscaNo(idCauda);
    Node* cabeca = buscaNo(idCabeca);

    if(cauda == nullptr){
        this->insereNoFim(idCauda);
        cauda = this->ultimoNo;
    }
    if(cabeca == nullptr){
        this->insereNoFim(idCabeca);
        cabeca = this->ultimoNo;
    }

    cauda->insereAresta(idCauda, idCabeca, peso);

    if(!this->digrafo){
        cabeca->insereAresta(idCabeca, idCauda, peso);
    }
}

void Graph::imprime(){
    //TODO: Adicionar a impressao das arestas também
    Node* no =  this->primeiroNo;

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr)
    {
        cout << "(" << no->getId() << ")" << endl;
        Edge* aresta = no->getPrimeiraAresta();
        cout << "\t";
        while (aresta != nullptr )
        {
            cout << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        cout << endl;

        no = no->getProxNo();
    }
}

void Graph::imprimeInvertido(){
    //TODO: Adicionar a impressao das arestas também
    Graph::imprimeInvertidoAux(this->primeiroNo);
}

void Graph::imprimeInvertidoAux(Node* no){
    if(no == nullptr){
        return;
    }

    imprimeInvertidoAux(no->getProxNo());
    cout << "(" << no->getId() << ")" << endl;
}

bool Graph::getDigrafo()
{
    return this->digrafo;
}

int Graph::getGrauNo(int id)
{
    Node* no = buscaNo(id);

    if(!getDigrafo())
    {
        return no->getGrauNo();
    }
    else{
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }

}

int Graph::getEntradaNo(int id)
{
    Node* no = buscaNo(id);

    if(getDigrafo())
    {
        return no->getEntradaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }

}

int Graph::getSaidaNo(int id)
{
    Node* no = buscaNo(id);

    if(getDigrafo())
    {
        return no->getSaidaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }
}

bool Graph::getKRegularidade(int k)
{
    Node* no = this->primeiroNo;

    if(no->getGrauNo() != k){
        return false;
    }
    else{
        while (no != nullptr)
        {
            if(no->getGrauNo() != k){ //caso tenha grau diferente de k retorna false
                return false;
            }

            no = no->getProxNo(); //se tinha grau k passa para o próximo
        }
        return true; // se não retornou false depois de passar por todos retorna true
    }
}

int Graph::getOrdem()
{
    return this->ordem;
}

bool Graph::isTrivial()
{
    Node* no = this->primeiroNo;
    
    if(no->getProxNo() == nullptr){ // se o próximo do primeiro for null é pq só possui um no
        return true;
    }
    else{
        return false;
    }
}

bool Graph::isNulo()
{
    Node* no = this->primeiroNo;

    if(no == nullptr){
        return true;
    }
    else{
        return false;
    }
}


int Graph::getGrauGrafo() // não está adaptado para um digrafo 
{
    Node* no = this->primeiroNo;
    int grau = no->getGrauNo();

    while (no != nullptr)
    {
        if(no->getGrauNo() > grau){ //caso tenha grau maior que o anterior, atualiza o valor de grau
            grau = no->getGrauNo();
        }

        no = no->getProxNo(); // passa para o próximo
    }
    return grau; // retorna o maior grau entre os nos do grafo
}