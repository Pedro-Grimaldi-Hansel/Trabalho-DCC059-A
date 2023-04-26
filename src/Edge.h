#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

class Edge
{
private:
    Edge* proxAresta;
    float peso;
    int idCauda;
    int idCabeca;
public:
    Edge();
    Edge(int idCauda, int idCabeca, float peso);
    Edge(Edge* proxAresta, float peso, int idCauda, int idCabeca);
    ~Edge();

    float getPeso();
    void setPeso(float peso);

    int getIdCauda();
    void setIdCauda(int idCauda);

    int getIdCabeca();
    void setIdCabeca(int idCabeca);

    Edge* getProxAresta();
    void setProxAresta(Edge* aresta);
};

#endif // EDGE_H_INCLUDED
