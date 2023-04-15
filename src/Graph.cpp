#include "Graph.h"

using namespace std;

Graph::Graph(bool digraph){
    this->digraph = digraph;
}

Graph::~Graph(){
    
}

VertexList* Graph::getVertices(){
    return this->vertices;
}

void Graph::setVertices(VertexList* vertices){
    this->vertices = vertices;
}

EdgeList* Graph::getEdges(){
    return this->edges;
}

void Graph::setEdges(EdgeList* edges){
    this->edges = edges;
}

bool Graph::getDigraph(){
    return this->digraph;
}