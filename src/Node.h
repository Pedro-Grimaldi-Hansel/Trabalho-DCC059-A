#include "Edge.h"

using namespace std;

class Node
{
private:
    Edge* primeiraAresta;
    int id;
    Node* proxNo;
public:
    Node(Edge* primeiraAresta, int id, Node* proxNo);
    ~Node();
};
