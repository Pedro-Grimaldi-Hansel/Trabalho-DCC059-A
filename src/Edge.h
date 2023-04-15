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
    Edge(Edge* proxAresta, float peso, int idCauda, int idCabeca);
    ~Edge();
};

#endif // EDGE_H_INCLUDED
