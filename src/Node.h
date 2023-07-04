#include "Edge.h"
#include <iostream>

using namespace std;

class Node
{
private:
    Edge* primeiraAresta;
    int idAplicacao;    // id Da nossa aplicação (Serve somente para a inserção!)
    int idArquivo;      // id do arquivo
    Node* proxNo;
    int grauNo;
    int grauReativo;
    float peso;

    // colocando valores para grau de entrada e saída caso digrafo
    int grauEntradaNo;
    int grauSaidaNo;

    int excentricidade;

public:
    Node();
    Node(int idAplicacao);
    ~Node();


    void insereAresta(int idCabeca, float peso); //Recebe o id de arquivo
    Edge* buscaAresta(int idCabeca);             //Recebe o id de arquivo  
    bool removeAresta(int idCabeca);             //Recebe o id de arquivo

    int getGrauNo();
    int getGrauReativo();
    int getEntradaNo();
    int getSaidaNo();
    int getIdArquivo();
    float getPesoNo();
    Node* getProxNo();
    Edge* getPrimeiraAresta();

    void setIdArquivo(int idArquivo);
    void setGrauNo(int grau);
    void setGrauReativo(int grau);
    void setEntradaNo(int grau);
    void setSaidaNo(int grau);
    void setPesoNo(float peso);
    void setProxNo(Node* proximo);

    int getExcentricidadeNo();
    void setExcentricidadeNo(int excentricidade);

    float getPrioridade();

};
