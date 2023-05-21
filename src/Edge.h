#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

class Edge
{
private:
    Edge* proxAresta;
    float peso;
    int idCabeca;
public:
    Edge();
    Edge(int idCabeca, float peso);
    Edge(Edge* proxAresta, float peso, int idCabeca);
    ~Edge();

    float getPeso();
    void setPeso(float peso);

    int getIdCabeca();
    void setIdCabeca(int idCabeca);

    Edge* getProxAresta();
    void setProxAresta(Edge* aresta);
};

#endif // EDGE_H_INCLUDED
