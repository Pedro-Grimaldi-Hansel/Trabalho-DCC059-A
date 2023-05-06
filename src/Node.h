#include "Edge.h"
#include <iostream>

using namespace std;

class Node
{
private:
    Edge* primeiraAresta;
    int id;
    Node* proxNo;
public:
    Node();
    Node(int id);
    ~Node();

    void setProxNo(Node* proximo);
    Node* getProxNo();
    int getId();
    void setId(int id);
    Edge* getPrimeiraAresta();

    //TODO: Implementar a inserção de aresta no no
    void insereAresta(int idCauda, int idCabeca, float peso);
    Edge* buscaAresta(int idCauda, int idCabeca);
    void removeAresta(int idCauda, int idCabeca);
};
