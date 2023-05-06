#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(bool digrafo){
    this->digrafo = digrafo;
    this->primeiroNo = nullptr;
    this->ultimoNo = nullptr;
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
        this->primeiroNo = no;
        this->ultimoNo = no;
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

void Graph::removeAresta(int idCauda, int idCabeca){
    //busca Nos
    Node* cauda = buscaNo(idCauda);
    Node* cabeca = buscaNo(idCabeca);

    if(cauda == nullptr || cabeca == nullptr){
        cout << "Aresta inexiste" << endl;
        return;
    }
    
    //chama a remoção de aresta do no
    cauda->removeAresta(idCauda, idCabeca);

    //verifica se o não for digrafo tem que remover a aresta na cabeça também
    if(!this->digrafo){
        cabeca->removeAresta(idCabeca, idCauda);
    }
}

void Graph::imprime(){
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