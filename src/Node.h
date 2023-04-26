#include "Edge.h"

using namespace std;

class Node
{
private:
    Edge* primeiraAresta;
    int id;
    Node* proxNo;
    int grauNo;

    // colocando valores para grau de entrada e saída caso digrafo
    int grauEntradaNo;
    int grauSaidaNo;

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

    int getGrauNo();
    int getEntradaNo();
    int getSaidaNo();

};
