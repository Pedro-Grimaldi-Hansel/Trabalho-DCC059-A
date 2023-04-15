#include "VertexList.h"
#include "EdgeList.h"

class Graph {
    public:
        Graph(bool digraph);
        ~Graph();
        VertexList* getVertices();
        void setVertices(VertexList* vertices);
        EdgeList* getEdges();
        void setEdges(EdgeList* edges);
        bool getDigraph();

    private:
        VertexList* vertices;
        EdgeList* edges;
        bool digraph;
};