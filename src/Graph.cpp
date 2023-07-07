#include "Graph.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>
#include <chrono>
#include <ctime>
#include <set>
#include <stack>
#include <random>
#include <map>
#include <algorithm>


using namespace std;
using namespace chrono;

Graph::Graph(ifstream &arquivoEntrada, bool digrafo, bool ponderadoAresta, bool ponderadoVertice)
{
    if(!arquivoEntrada.is_open())
    {
        cout << "ERRO: Arquivo não aberto corretamente!" << endl;
        return;
    }

    this->ultimoIdVinculado = 0;
    this->digrafo = digrafo;
    this->ordem = 0;
    this->pesoNasArestas = ponderadoAresta;
    this->pesoNosVertices = ponderadoVertice;
    
    string leitor;
    int ordemGrafo;
    int numArestas;
    int idCauda;
    int idCabeca;
    float pesoAresta = 0;

    // Pegar primeira linha e ver o número de nós e arestas
    arquivoEntrada >> ordemGrafo;
    arquivoEntrada >> numArestas;

    cout << "A ordem do grafo é: " << ordemGrafo << endl;
    cout << "o grafo tem " << numArestas << " arestas"<< endl;

    // Insere todos o vértices
    for(int i = 0; i < ordemGrafo; i++)
    {
        this->insereNoFim(i+1);
    }

    if(ponderadoVertice && !ponderadoAresta)
    {
        //Pegar linha até o fim do arquivo
        while( arquivoEntrada >> leitor >> idCauda >> idCabeca) 
        {
            this->insereAresta(idCauda, idCabeca, pesoAresta);
        }
    }
    else
    {
        cout << "ERROR: Leitura ainda não implementada!" << endl;
    }
}

Graph::Graph(ifstream &arquivoEntrada)
{
    if(!arquivoEntrada.is_open())
    {
        cout << "ERRO: Arquivo não aberto corretamente!" << endl;
        return;
    }

    // Para o trabalho temos instancias não direcionadas, sem peso nas arestas e peso nos vétices
    this->digrafo = false;
    this->pesoNasArestas = false;
    this->pesoNosVertices = true;
    this->ordem = 0;
    
    string leitor;
    int ordemGrafo;
    int numArestas;
    int idCauda;
    int idCabeca;

    // Pegar primeira linha e ver o número de nós e arestas
    arquivoEntrada >> ordemGrafo;
    arquivoEntrada >> numArestas;

    cout << "A ordem do grafo é: " << ordemGrafo << endl;
    cout << "o grafo tem " << numArestas << " arestas"<< endl;

    this->numArestas = numArestas;

    for(int i = 1; i <= ordemGrafo; i++ ){
        insereNoFim(i, i);
    }

    while( arquivoEntrada >> leitor >> idCauda >> idCabeca) {
        this->insereArestaTrabalho(idCauda, idCabeca);
    }
}

Graph::~Graph() { }

void Graph::escreveArquivo(ofstream &arquivoSaida)
{
    // Verificar se o arquivo foi aberto corretamente
    if (!arquivoSaida.is_open()) 
    {
        cout << "Erro ao abrir o arquivo " << endl;
        return;
    }

    arquivoSaida << this->getOrdem() << endl;

    // Escrever as arestas do grafo
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo())
    {
        for(Edge* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            if(no->getIdArquivo() > aresta->getIdCabeca())
            {
                continue; // Para não repetir aresta
            }
            arquivoSaida << no->getIdArquivo();
            arquivoSaida << " " << aresta->getIdCabeca();
            arquivoSaida << " " << aresta->getPeso() << endl;
        }
    }
}

void Graph::escreveArquivoDOT(ofstream &arquivoSaida)
{
    // Verificar se o arquivo foi aberto corretamente
    if (!arquivoSaida.is_open()) 
    {
        cout << "Erro ao abrir o arquivo " << endl;
        return;
    }
    
    // Escrever o cabeçalho do arquivo DOT
    if(this->digrafo)
    {
        arquivoSaida << "digraph Grafo {" << endl;
    }
    else
    {
        arquivoSaida << "graph Grafo {" << endl;
    }
    
    // Escrever as arestas do grafo
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo())
    {
        for(Edge* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            if(no->getIdArquivo() < aresta->getIdCabeca())
            {
                continue; //Para não repetir aresta
            }
            arquivoSaida << "    " << no->getIdArquivo();
            if(this->digrafo)
            {
                arquivoSaida << " -> ";
            }
            else
            {
                arquivoSaida << " -- ";
            }
            arquivoSaida << aresta->getIdCabeca();
            arquivoSaida << " [label = \"" << aresta->getPeso() << "\"] ";
            arquivoSaida << ";" << endl;
        }
    }
    
    // Escrever o fechamento do arquivo DOT
    arquivoSaida << "}" << endl;
    
    // Fechar o arquivo
    arquivoSaida.close();
    
    cout << "Arquivo criado com sucesso!" << endl;
}

Node* Graph::getPrimeiroNo()
{
    return this->primeiroNo;
}

// Somente utilizado para nós já inseridos!
void Graph::vinculaNo(int idArquivo)
{
    Node* no = this->ultimoNoVinculado; // Pega o último nó vinculado

    if(no == nullptr) // Caso o último nó vinculado seja null
    { 
        this->ultimoNoVinculado = this->primeiroNo; // Último nó vinculado recebe o primeiro nó
    }
    else
    {
        this->ultimoNoVinculado = no->getProxNo(); // Atualiza o último nó vinculado
        if(this->ultimoNoVinculado == nullptr)
        {
            printf("Ordem do Grafo ultrapassada! Insira um nó!");
            return;
        }
    }
    no = this->ultimoNoVinculado; // Nó revebe o último nó vinculado
    no->setIdArquivo(idArquivo); // Vincula o nó
    if(this->pesoNosVertices)
    {
        no->setPesoNo( (idArquivo % 200) + 1);
    }
    this->ultimoIdVinculado += 1; // Incrementar o último vinculado
}

void Graph::insereNoFim(int id)
{
    Node* no = new Node(id);
    no->setProxNo(nullptr);

    if(this->primeiroNo == nullptr) // Caso o grafo esteja vazio, insere no início 
    {
        this->primeiroNo = no;
        this->ultimoNo = no;
    }
    else
    {
        this->ultimoNo->setProxNo(no);
        this->ultimoNo = no;
    }
    this->ordem++;
}

void Graph::insereNoFim(int id, int idArquivo)
{
    Node* no = new Node(id);
    no->setIdArquivo(idArquivo);
    no->setProxNo(nullptr);

    // Setando o peso do vértice conforme o trabalho
    no->setPesoNo( (idArquivo % 200) + 1 );

    if(this->primeiroNo == nullptr) // Caso o grafo esteja vazio, insere no início mesmo
    {
        this->primeiroNo = no;
        this->ultimoNo = no;
    }
    else
    {
        this->ultimoNo->setProxNo(no);
        this->ultimoNo = no;
    }
    this->ordem++;
}

Node* Graph::buscaNoPorIdArquivo(int idArquivo)
{
    Node* no = this->primeiroNo; // Auxiliar para busca

    while (no != nullptr)
    {
        if(no->getIdArquivo() == idArquivo) // Caso encontrou o nó retorna ele
        { 
            return no;
        }

        no = no->getProxNo(); // Se não encontrou passa para o próximo
    }
    // Caso nao tenha encontrado nenhum, retorna nullptr
    return nullptr;
}

void Graph::insereArestaTrabalho(int idCauda, int idCabeca)
{
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr)
    {
        this->insereNoFim(idCauda, idCauda);
        cauda = this->ultimoNo;
    }
    if(cabeca == nullptr)
    {
        this->insereNoFim(idCabeca, idCabeca);
        cabeca = this->ultimoNo;
    }

    cauda->insereAresta(idCabeca, 0);

    if(!this->digrafo)
    {
        cabeca->insereAresta(idCauda, 0);
    }

    if(!this->getDigrafo())
    {
        cabeca->setGrauNo(cabeca->getGrauNo() + 1);
        cabeca->grauBackup = cabeca->getGrauNo(); 
        cauda->setGrauNo(cauda->getGrauNo() + 1);
        cauda->grauBackup = cauda->getGrauNo();
    }
    else
    {
        cabeca->setEntradaNo(cabeca->getEntradaNo() + 1);
        cauda->setSaidaNo(cauda->getSaidaNo() + 1);
    }
}

void Graph::insereAresta(int idCauda, int idCabeca, float peso)
{
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr)
    {
        this->vinculaNo(idCauda);
        cauda = this->ultimoNoVinculado;
    }
    if(cabeca == nullptr)
    {
        this->vinculaNo(idCabeca);
        cabeca = this->ultimoNoVinculado;
    }

    cauda->insereAresta(idCabeca, peso);

    if(!this->digrafo)
    {
        cabeca->insereAresta(idCauda, peso);
    }

    if(!this->getDigrafo())
    {
        cabeca->setGrauNo(cabeca->getGrauNo() + 1);
        cauda->setGrauNo(cauda->getGrauNo() + 1);
    }
    else
    {
        cabeca->setEntradaNo(cabeca->getEntradaNo() + 1);
        cauda->setSaidaNo(cauda->getSaidaNo() + 1);
    }

    setNumArestas(getNumArestas()+1);
}

void Graph::removeAresta(int idCauda, int idCabeca)
{
    // Busca Nós
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr || cabeca == nullptr)
    {
        cout << "Aresta inexiste" << endl;
        return;
    }
    
    // Chama a remoção de aresta do nó
    bool removido = cauda->removeAresta(idCabeca);
    if(removido)
    {
        if(this->digrafo)
        {
            cauda->setSaidaNo(cauda->getSaidaNo() - 1);
        }
        else
        {
            cauda->setGrauNo(cauda->getGrauNo() - 1);
        }
    }

    // verifica se o não for digrafo tem que remover a aresta na cabeça também
    if(!this->digrafo)
    {
        removido = cabeca->removeAresta(idCauda);
        if(removido)
        {
            cabeca->setGrauNo(cabeca->getGrauNo() - 1);
        }
    }

    setNumArestas(getNumArestas()-1);
}

bool Graph::removeNo(int idArquivo)
{
    Node* no = this->primeiroNo;
    Node* noAnteriror = nullptr;

    if(this->primeiroNo == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return false;
    }

    // Percorre todos os nós armazenando o atual e anterior
    while(no != nullptr){
        if(no->getIdArquivo() == idArquivo)
        {
            break; // Encontrou o nó
        }
        noAnteriror = no;
        no = no->getProxNo();
    }

    // Nó não encontrado
    if(no == nullptr)
    {
        cout << "Nó não encotrado!" << endl;
        return false;
    }

    // Remove todas as arestas
    for(Node* nodeAux = this->primeiroNo; nodeAux != nullptr; nodeAux = nodeAux->getProxNo())
    {
        if(nodeAux->getIdArquivo() == idArquivo)
        {
            // Estamos no nó que queremos deletar
            Node* noASerDecrementado;
            for(Edge* aresta = nodeAux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
            {
                noASerDecrementado = buscaNoPorIdArquivo(aresta->getIdCabeca());
                noASerDecrementado->setEntradaNo( noASerDecrementado->getEntradaNo() - 1 );
            }

        }
        else 
        {
            for(Edge* aresta = nodeAux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
            {
                if(aresta->getIdCabeca() ==  idArquivo)
                {
                    nodeAux->removeAresta(idArquivo);

                    if(this->digrafo)
                    {
                        // Decrementa o grau de saída
                        nodeAux->setSaidaNo( nodeAux->getSaidaNo() - 1);
                    }
                    else
                    {
                        // Decrementa o grau do nó
                        nodeAux->setGrauNo(nodeAux->getGrauNo() - 1);
                    }
                }
            }
        }
    }

    if(noAnteriror == nullptr)
    {
        // o nó é a primeira da lista
        this->primeiroNo = no->getProxNo();
    }
    else if(no->getProxNo() == nullptr)
    {
        // o nó é a ultima da lista
        noAnteriror->setProxNo(nullptr);
    }
    else
    {
        // o nó está no meio
        noAnteriror->setProxNo(no->getProxNo());
    }
    
    this->ordem--;
    delete no;
    return true;
}

void Graph::imprime()
{
    Node* no =  this->primeiroNo;

    if(no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr)
    {
        cout << "(" << no->getIdArquivo() << ")";
        if(this->pesoNosVertices)
        {
            cout << "<peso: " << no->getPesoNo() << " >";
        }
        cout << endl;
        Edge* aresta = no->getPrimeiraAresta();
        cout << "\t";
        while (aresta != nullptr )
        {
            cout << aresta->getIdCabeca();
            if(this->pesoNasArestas)
            {
                cout << " (" << aresta->getPeso() << ")";
            }
                cout <<", ";
            aresta = aresta->getProxAresta();
        }
        cout << endl;

        no = no->getProxNo();
    }
}

bool Graph::getDigrafo()
{
    return this->digrafo;
}

int Graph::getGrauNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(!getDigrafo())
    {   
        return no->getGrauNo();
    }
    else
    {
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }

}

int Graph::getNumArestas()
{
    return this->numArestas;
}

void Graph::setNumArestas(int numArestas)
{
    this->numArestas = numArestas;
}

bool Graph::getKRegularidade(int k)
{
    Node* no = this->primeiroNo;

    if(no->getGrauNo() != k)
    {
        return false;
    }
    else
    {
        while (no != nullptr)
        {
            if(no->getGrauNo() != k) // caso tenha grau diferente de k retorna false
            { 
                return false;
            }

            no = no->getProxNo(); // se tinha grau k passa para o próximo
        }
        return true; // se não retornou false depois de passar por todos retorna true
    }
}

int Graph::getOrdem()
{
    return this->ordem;
}

bool Graph::isTrivial()
{
    Node* no = this->primeiroNo;
    
    if(no->getProxNo() == nullptr) // se o próximo nó do primeiro for null é pq só possui um nó
    { 
        return true;
    }
    else
    {
        return false;
    }
}

bool Graph::isNulo()
{
    Node* no = this->primeiroNo;

    if(no == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Graph::getGrauGrafo() // não está adaptado para um digrafo 
{
    Node* no = this->primeiroNo;
    int grau = no->getGrauNo();

    while (no != nullptr)
    {
        if(no->getGrauNo() > grau) // caso tenha grau maior que o anterior, atualiza o valor de grau
        { 
            grau = no->getGrauNo();
        }

        no = no->getProxNo(); // passa para o próximo
    }
    return grau; // retorna o maior grau entre os nos do grafo
}

int* Graph::sequenciaDeGraus() // não está adaptado para um digrafo
{     
    if (this == nullptr || this->primeiroNo == nullptr || getOrdem() <= 0) 
    {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }

    Node* no = this->primeiroNo;
    int* sequencia=new int[getOrdem()];

    if(no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }
    else
    {
        for(int i = 0; i < getOrdem(); i++)
        {
            if (no != nullptr) 
            {
                sequencia[i] = no->getGrauNo();
                no = no->getProxNo();
            } else 
            {
                // nó é nulo, definir grau como zero
                sequencia[i] = 0;
            }
        }
    }
    return sequencia;
}

void Graph::vizinhancaAberta(int id)
{
    Node* no = buscaNoPorIdArquivo(id);
    Edge* aresta = no->getPrimeiraAresta();
    std::vector< int > vizinhancaAberta;

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta())
    {
        vizinhancaAberta.push_back(aresta->getIdCabeca());
    }
    cout << "A vizinhança aberta é: " << endl; 
    for (int i = 0; i < vizinhancaAberta.size(); i++) 
    {
        cout << vizinhancaAberta[i] << " ";
    }
    cout << endl;

    return;
}

void Graph::vizinhancaFechada(int id)
{
    Node* no = buscaNoPorIdArquivo(id);
    Edge* aresta = no->getPrimeiraAresta();
    std::vector< int > vizinhancaFechada;

    vizinhancaFechada.push_back(id);

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta())
    {
        vizinhancaFechada.push_back(aresta->getIdCabeca());
    }
    
    cout << "A vizinhança fechada é: " << endl; 
    for (int i = 0; i < vizinhancaFechada.size(); i++) 
    {
        cout << vizinhancaFechada[i] << " ";
    }
    cout << endl;

    return;
}

int Graph::getNumberOfNodes()
{
    return this->getOrdem();
}

int Graph::getNumberOfEdges()
{
    return this->numArestas; 
}

bool Graph::isComplete()
{
    int n = getNumberOfNodes();
    int edgesToBeComplete = n*(n-1)/2;
    return (getDigrafo() && getNumberOfEdges() == edgesToBeComplete*2) || (!getDigrafo() &&  getNumberOfEdges() == edgesToBeComplete);
}

// Função de busca em largura (Breadth-first search)
bool Graph::BFS()
{
    Node* root = getPrimeiroNo(); 
    int numberOfNodes = getNumberOfNodes();
    vector<bool> visited(numberOfNodes, false);

    list<Node*> queue; // Fila para visita
    visited[root->getIdArquivo()] = true; // Marca o primeiro como visitado
    queue.push_back(root); // Coloca o primeiro nó fim da fila

    while (!queue.empty()) 
    {
        Node* nextNode = queue.front();
        cout << nextNode->getIdArquivo() << " ";
        queue.pop_front();

        Edge* currentEdge = nextNode->getPrimeiraAresta();
        while (currentEdge != nullptr) 
        {
            int headNodeId = currentEdge->getIdCabeca();
            Node* headNode = buscaNoPorIdArquivo(headNodeId);

            if (!visited[headNode->getIdArquivo()]) 
            {
                visited[headNode->getIdArquivo()] = true;
                queue.push_back(headNode);
            }

            currentEdge = currentEdge->getProxAresta();
        }
    }

    return true;
}

// BFS auxiliar para saber se é bipartido onde há colocarção dos nós parasaber se há uma possível bipartição
bool Graph::BFSColoring(int startNode, vector<int>& color, vector<bool>& visited)
{
    color[startNode] = 1;  // Colore o primeiro nó com a cor 1
    list<int> queue; // Fila para visita
    queue.push_back(startNode); // Coloca o primeiro nó na fila
    visited[startNode] = true; // Marca o primeiro como visitado

    while (!queue.empty()) 
    {
        int currentNode = queue.front();
        queue.pop_front();

        Edge* currentEdge = buscaNoPorIdArquivo(currentNode+1)->getPrimeiraAresta();

        while (currentEdge != nullptr) 
        {
            int neighborNode = currentEdge->getIdCabeca();
            neighborNode--;

            if (!visited[neighborNode]) 
            {
                visited[neighborNode] = true;
                color[neighborNode] = 1 - color[currentNode];  // Colore o nó vizinho com a cor oposta
                queue.push_back(neighborNode);
            } 
            else if (color[neighborNode] == color[currentNode]) 
            {
                return false;  // Achou aresta com extremidades em nós da mesma cor
            }

            currentEdge = currentEdge->getProxAresta();
        }
    }

    return true;  // Grafo é Bipartido
}

// Grafo bipartido é grafo cujos vértices podem ser divididos em dois conjuntos disjuntos U e V tais que toda aresta conecta um vértice em U a um vértice em V; ou seja, U e V são conjuntos independentes.
bool Graph::isBipartide()
{

    int numberOfNodes = getNumberOfNodes();
    int numberOfEdges = getNumberOfEdges();

    // Verificação Básica Inicial
    if(getDigrafo() && numberOfEdges > ((numberOfNodes*numberOfNodes)/2) || !getDigrafo() && numberOfEdges > ((numberOfNodes*numberOfNodes)/4))
    {
        return false;
    }
    else
    {
        vector<int> color(numberOfNodes, -1);  // Todos os nós são iniciados com cor -1
        vector<bool> visited(numberOfNodes, false);

        for (int i = 0; i < numberOfNodes; i++) 
        {
            if (!visited[i]) 
            {
                if (!BFSColoring(i, color, visited)) 
                {
                    return false;  // Grafo não é Bipartido
                }
            }
        }
        return true;  // Grafo Bipartido
    }
}

bool Graph::isEulerian()
{
    int numberOfNodes = getNumberOfNodes();
    int numberOfEdges = getNumberOfEdges();

    if (getDigrafo()) 
    {
        // Verifica se todos os nós possuem os mesmos graus de entrada e de saída, menos grafos com self-loops
        for (Node* node = getPrimeiroNo(); node != nullptr; node = node->getProxNo()) 
        {
            if (node->getEntradaNo() != node->getSaidaNo()) 
            {
                if (node->getEntradaNo() != node->getSaidaNo() || node->getEntradaNo() % 2 != 0) 
                {
                    return false;
                }
            }
        }
    } 
    else 
    {
        int selfLoopsCount = 0;
        // Contagem de arestas incidentes em cada nó
        vector<int> degreeCount(numberOfNodes, 0);  

        for (Node* node = getPrimeiroNo(); node != nullptr; node = node->getProxNo()) 
        {
            Edge* currentEdge = node->getPrimeiraAresta();
            while (currentEdge != nullptr) 
            {
                int headNode = currentEdge->getIdCabeca();
                degreeCount[headNode]++;
                degreeCount[node->getIdArquivo()]++;
                currentEdge = currentEdge->getProxAresta();
            }
            // Self-loops
            if (degreeCount[node->getIdArquivo()] > 0) 
            {
                selfLoopsCount += degreeCount[node->getIdArquivo()] / 2;
            }
        }
        // Verifica se todos os nós (exceto self-loops) possuem grau par, e os nós com self-loops possuem grau par ou múltiplo de 2
        for (int i = 0; i < numberOfNodes; i++) 
        {
            if (degreeCount[i] % 2 != 0) 
            {
                if (degreeCount[i] % 2 != 0 || degreeCount[i] % 4 != 0) 
                {
                    return false;
                }
            }
        }
        // Verifica se o número de self-loops é par
        if (selfLoopsCount % 2 != 0) 
        {
            return false;
        }
    }
    // Verifica se o grafo é conexo
    if (!BFS())
    {
        return false;
    }
    return true;
}

// Busca por profundidade
void Graph::DFS(int idInitialNode)
{
    int numberOfNodes = getNumberOfNodes();
    vector<bool> visited(numberOfNodes, false);

    // Modificação do índice por causa da diferença nas instâncias (vai de 1 a n e não de 0 a n-1)
    visited[idInitialNode+1] == true;
    Edge* currentEdge = buscaNoPorIdArquivo(idInitialNode+1)->getPrimeiraAresta();

    for(currentEdge; currentEdge != nullptr; currentEdge = currentEdge->getProxAresta())
    {
        if(!visited[currentEdge->getIdCabeca() + 1])
        {
            DFS(currentEdge->getIdCabeca() + 1);
        }
    }
    cout << "Vértice atual (DFS): " << idInitialNode << endl;

}

// DFS para arestas ponte
void Graph::bridgesDFS(int initial, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<Edge*> &bridges) 
{
    // disc = discovery -> tempo de descoberta
    static int time = 0;
    int u = initial;

    Edge* currentEdge = buscaNoPorIdArquivo(u+1)->getPrimeiraAresta();
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (currentEdge; currentEdge != nullptr; currentEdge = currentEdge->getProxAresta()) 
    {
        int v = currentEdge->getIdCabeca()-1;

        if (!visited[v]) 
        {
            parent[v] = u;
            bridgesDFS(v, visited, disc, low, parent, bridges);

            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u])
            {
                bridges.push_back(currentEdge);
            }
        } 
        else if (v != parent[u]) 
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<Edge*> Graph::findBridges() 
{
    vector<Edge*> bridges;
    int numberOfNodes = getNumberOfNodes();
    vector<bool> visited(numberOfNodes, false);
    vector<int> disc(numberOfNodes, 0);
    vector<int> low(numberOfNodes, 0);
    vector<int> parent(numberOfNodes, -1);

    for (int i=0; i < numberOfNodes; i++) 
    {
        if (!visited[i])
            bridgesDFS(i, visited, disc, low, parent, bridges);
    }

    return bridges;
}

set<int> Graph::findArticulationNodes()
{
    set<int> articulationNodes;
    vector<Edge*> bridges = findBridges();
    for(int i = 0; i < bridges.size(); i++)
    {
        articulationNodes.insert(bridges[i]->getIdCabeca());
        articulationNodes.insert(bridges[i]->getIdCauda());
    }
    return articulationNodes;
}

void Graph::stronglyConnectedComponents() 
{
    stack<Node*> nodeStack;
    unordered_set<Node*> visitedNodes;
    // Percorre o grafo e preenche a pilha com a ordem de finalização dos nós
    for (Node* node = primeiroNo; node != nullptr; node = node->getProxNo()) 
    {
        DFSSCC(node, nodeStack, visitedNodes);
    }
    // Inverte todas as arestas do grafo
    Graph* transposedGraph = new Graph();
    transposedGraph = getTransposedGraph();
    // Realiza uma DFS no grafo transposto e encontra as componentes fortemente conexas
    visitedNodes.clear(); 
    int componentIndex = 1;
    while (!nodeStack.empty()) 
    {
        Node* node = nodeStack.top();
        nodeStack.pop();

        if (visitedNodes.find(node) == visitedNodes.end()) 
        {
            vector<int> components;
            transposedGraph->DFSSCCAUX(node, visitedNodes, componentIndex, components);
            cout << "Componente Fortemente Conexa " << componentIndex << ": ";
            for (int i = 0; i < components.size(); i++) 
            {
                cout << components[i] << " ";
            }
            cout << endl;
            componentIndex++;
        }
    }
}

void Graph::DFSSCC(Node* node, stack<Node*>& nodeStack, unordered_set<Node*>& visitedNodes) 
{
    visitedNodes.insert(node);
    // Recorrer para todos os nós adjacentes não visitados
    for (Edge* edge = node->getPrimeiraAresta(); edge != nullptr; edge = edge->getProxAresta()) 
    {
        Node* adjacentNode = buscaNoPorIdArquivo(edge->getIdCabeca());
        if (adjacentNode && visitedNodes.find(adjacentNode) == visitedNodes.end()) 
        {
            DFSSCC(adjacentNode, nodeStack, visitedNodes);
        }
    }
    // Adicionar o nó à pilha após percorrer todos os seus vizinhos
    nodeStack.push(node);
}

void Graph::DFSSCCAUX(Node* node, unordered_set<Node*>& visitedNodes, int componentIndex, vector<int>& components) 
{
    // Se for uma DFS no grafo transposto, adicionar o nó à componente
    if (componentIndex != -1) 
    {
        components.push_back(node->getIdArquivo());
    }
    // Recorrer para todos os nós adjacentes não visitados
    for (Edge* edge = node->getPrimeiraAresta(); edge != nullptr; edge = edge->getProxAresta()) 
    {
        Node* adjacentNode = buscaNoPorIdArquivo(edge->getIdCabeca());
        if (adjacentNode && visitedNodes.find(adjacentNode) == visitedNodes.end()) 
        {
            DFSSCCAUX(adjacentNode, visitedNodes, componentIndex, components);
        }
    }
}

Graph::Graph() 
{
    primeiroNo = nullptr;
    ultimoNo = nullptr;
    digrafo = true;
    pesoNasArestas = false;
    pesoNosVertices = false;
    numArestas = 0;
}

Graph* Graph::getTransposedGraph() 
{
    Graph* transposedGraph  = new Graph();
    // Criação de nós no grafo transposto
    for (Node* node = primeiroNo; node != nullptr; node = node->getProxNo()) 
    {
        transposedGraph->insereNoFim(node->getIdArquivo());
    }
    // Inversão das arestas
    for (Node* node = primeiroNo; node != nullptr; node = node->getProxNo()) 
    {
        Edge* edge = node->getPrimeiraAresta();
        while (edge != nullptr) 
        {
            transposedGraph->insereAresta(edge->getIdCabeca(), node->getIdArquivo(), edge->getPeso());
            edge = edge->getProxAresta();
        }
    }
    return transposedGraph;
}

void Graph::AGM()
{
    std::vector< Edge > arestas;
    Node* no = this->primeiroNo;
    std::vector< Edge > AGM; // essa será a solução
     // criar um vetor para auxiliar quanto a formação de ciclos
    int i=0;
    int numNos = this->getOrdem();
    int subarvores[numNos]; // vetor solução
    int mapa[numNos]; // vetor de mapeamento idArquivo->subarvore
    // inicializar vetores auxiliares (aproveitando esse msm while)

    while(no != nullptr) // pegar todas as arestas do grafo e colocar no vetor
    { 
        Edge* primeiraAresta = no->getPrimeiraAresta();
        while(primeiraAresta!=nullptr)
        {
            if(this->getDigrafo() || primeiraAresta->getIdCabeca() < no->getIdArquivo()) // se for digrafo eu tenho q entrar de qqr forma, pois serão duas arestas diferentes
            { 
                arestas.push_back(*primeiraAresta); // se não for digrafo esse if ajuda a evitar pegar as arestas "duplicadas" que o grafo simples tem
            }
            primeiraAresta = primeiraAresta->getProxAresta();
        }
        subarvores[i] = mapa[i] = no->getIdArquivo();
        i++;
        no = no->getProxNo();
    }
    // ordenar as arestas em ordem crescente de peso
    quickSort(arestas, 0, arestas.size()-1);

    int contador = 0;
    i=0;

    while(contador < numNos-1 && i < arestas.size())
    {
        int indiceCaudaSubarvores = buscaNoVetor(mapa, arestas[i].getIdCauda(), numNos);
        int indiceCabecaSubarvores = buscaNoVetor(mapa, arestas[i].getIdCabeca(), numNos);

        if(subarvores[indiceCaudaSubarvores] != subarvores[indiceCabecaSubarvores]) // se forem iguais é pq estão na msm subarvores
        {
            // atualizar o vetor de subarvores
            atualizaSubarvores(numNos, subarvores, indiceCabecaSubarvores, indiceCaudaSubarvores);
            contador++;
            AGM.push_back(arestas[i]); // colocando a aresta na AGM
        }
        i++;
    }

    imprimeAGM(AGM, subarvores, mapa, numNos);
}

void Graph::imprimeAGM(vector< Edge > AGM, int subarvores[], int mapa[], int numNos)
{
    cout << "AGM: {";
    for(int i=0; i<AGM.size(); i++){
        cout << "(" << AGM[i].getIdCauda() << ", " << AGM[i].getIdCabeca() << "), ";
    }
    cout << "}" << endl;
}

// atualizar o vetor de subarvores
void Graph::atualizaSubarvores(int numNos, int subarvores[], int indiceCabecaSubarvores, int indiceCaudaSubarvores)
{
    for(int j=0; j<numNos; j++)
    { 
        if(subarvores[j] == subarvores[indiceCaudaSubarvores])
        {
            subarvores[j] = subarvores[indiceCabecaSubarvores];
        }
    }
}

int Graph::buscaNoVector(vector< int > vector, int valor, int tam)
{
    for(int i=0; i<tam; i++)
    {
        if(vector[i] == valor)
        {
            return i;
        }
    }
    return -1;
}

int Graph::buscaNoVectorNos(vector< Node > vector, int valor, int tam)
{
    for(int i=0; i<tam; i++)
    {
        if(vector[i].getIdArquivo() == valor)
        {
            return i;
        }
    }
    return -1;
}

int Graph::buscaNoVetor(int vetor[], int idArquivo, int tam)
{
    for(int i=0; i<tam; i++)
    {
        if(vetor[i] == idArquivo)
        {
            return i;
        }
    }
    return -1;
}

vector< Edge > Graph::OrdenaArestas(vector< Edge >arestas, int numArestas) // bubbleSort
{
    int aux;

    for (int k = 1; k < numArestas; k++) {
        for (int j = 0; j < numArestas - k; j++) {
            if (arestas[j].getPeso() > arestas[j+1].getPeso()) {
                aux = arestas[j].getPeso();
                arestas[j].setPeso(arestas[j+1].getPeso()); 
                arestas[j+1].setPeso(aux);
            }
        }
    }
    return arestas;
}

int partition(std::vector<Edge>& vetor, int low, int high) 
{
    int pivot = vetor[high].getPeso();
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) 
    {
        if (vetor[j].getPeso() <= pivot) 
        {
            i++;
            std::swap(vetor[i], vetor[j]);
        }
    }

    std::swap(vetor[i + 1], vetor[high]);
    return i + 1;
}

void Graph::quickSort(std::vector<Edge>& vetor, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(vetor, low, high);

        quickSort(vetor, low, pi - 1);
        quickSort(vetor, pi + 1, high);
    }
}

// ****** PARTE 2 DO TRABALHO ABAIXO *******

Solution Graph::coberturaMinimaGulosa()
{
    vector< pair< int, Node* > > candidatos;
    vector< int > solucao;
    float custoTotal = 0;
    double time = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    int j = 1;
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo(), j++)
    {
        if(no->getGrauNo() != 0)
        {
            candidatos.push_back(make_pair(j, no)); // remover todos os nós com grau 0
            candidatos[j-1].second->prioridade = candidatos[j-1].second->peso / candidatos[j-1].second->grauNo;
        }
    }

    int arestasCount = this->getNumArestas();

    while(candidatos.size() != 0)
    {
        sort(candidatos.begin(), candidatos.end(), [](pair<int, Node*> &a, pair<int, Node*> &b)
        {
            return a.second->prioridade < b.second->prioridade;
        }); // ordenar para ter na primeira posição o "mais ótimo" para a solução
        int idEscolhido = candidatos[0].second->idArquivo;
        solucao.push_back(idEscolhido); // coloca o "mais ótimo" candidato na solução
        custoTotal += candidatos[0].second->peso;

        // todo esse for é pra decrementar 1 no grau dos vizinhos do no adicionada à solução
        for(Edge* aresta=candidatos[0].second->primeiraAresta; aresta != nullptr; aresta=aresta->getProxAresta())
        {
            int firstVizinho = aresta->idCabeca; 
            //encontro o iterador do vizinho
            auto it = std::find_if(candidatos.begin(), candidatos.end(),
                          [firstVizinho](const pair<int, Node*> &ids)
                          {
                              return ids.first == firstVizinho;
                          });
            // decremento o grau
            if(it != candidatos.end())
            {
                int posicao = distance(candidatos.begin(), it);
                candidatos.at(posicao).second->setGrauNo(candidatos.at(posicao).second->grauNo - 1); 
                candidatos.at(posicao).second->prioridade = candidatos[posicao].second->peso / candidatos[posicao].second->grauNo;
                
                 // se o vizinho ficou com grau 0, removo 
                if(candidatos[posicao].second->grauNo == 0)
                {
                    candidatos.erase(candidatos.begin() + posicao);   
                }
            }
        }
        // remove o nó que foi  adicionado à solução
        candidatos.erase(candidatos.begin());   
    }
    
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop - start).count();

    verificaSolucao(solucao);
    // imprimir a solução
    Solution sol = Solution(custoTotal, solucao, time, 0);
    return sol;
}

Solution Graph::coberturaMinimaGulosaRandomizada(float alpha, int nInteracoes)
{
    high_resolution_clock::time_point start = high_resolution_clock::now();
    double time = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::srand(rd());
    vector< pair< int, Node* > > candidatos;
    vector< int > solucao;
    vector< int > solucaoBest;
    float custoTotal = 0;
    float custoBest = 0;

    for(int i=0; i < nInteracoes; i++)
    {
        int j = 1;
        for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo(), j++)
        {
            no->grauNo = no->grauBackup;
            if(no->getGrauNo() != 0)
            {// não adicionar os nós com grau 0
                candidatos.push_back(make_pair(j, no));
                candidatos[j-1].second->prioridade = candidatos[j-1].second->peso / candidatos[j-1].second->grauNo;
            }
        }
        solucao.clear();
        while(candidatos.size() != 0)
        {
            sort(candidatos.begin(), candidatos.end(), [](pair<int, Node*> &a, pair<int, Node*> &b){
                return a.second->prioridade < b.second->prioridade;
            }); // ordenar para ter na primeira posição o "mais ótimo" para a solução

            int numero_aleatorio = (int)(alpha*(candidatos.size()-1));
            if( numero_aleatorio == 0 )
                numero_aleatorio = 1;
            int k = std::rand() % numero_aleatorio; //Randomizao o numero de 0 a alpha*(vetorAuxiliar.size()-1)

            custoTotal += candidatos[k].second->peso;

            solucao.push_back(candidatos[k].second->idArquivo); // coloca o "mais ótimo" candidato na solução

                // todo esse for é pra decrementar 1 no grau dos vizinhos do no adicionada à solução
            Node* escolhido = candidatos[k].second;
            for(Edge* aresta=escolhido->primeiraAresta; aresta != nullptr; aresta=aresta->getProxAresta())
            {
                int firstVizinho = aresta->idCabeca; 
                //encontro o iterador do vizinho
                
                auto it = std::find_if(candidatos.begin(), candidatos.end(),
                            [firstVizinho](const pair<int, Node*> &ids)
                            {
                                return ids.first == firstVizinho;
                            });
                // decremento o grau
                if(it != candidatos.end()){
                    int posicao = distance(candidatos.begin(), it);
                    candidatos.at(posicao).second->setGrauNo(candidatos.at(posicao).second->grauNo - 1); 
                    candidatos.at(posicao).second->prioridade = candidatos[posicao].second->peso / candidatos[posicao].second->grauNo;

                    // se o vizinho ficou com grau 0, removo 
                    if(candidatos[posicao].second->grauNo == 0){
                        candidatos.erase(candidatos.begin() + posicao);   
                        candidatos.shrink_to_fit();
                    }
                }
            }
            // remove o nó que foi  adicionado à solução
            candidatos.erase(candidatos.begin()+k);
            candidatos.shrink_to_fit();
        }

        if(i == 0 || custoTotal < custoBest){
            custoBest = custoTotal;
            solucaoBest = solucao; 
        }  //Compara as soluçoes e atualiza a melhor
    }
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop - start).count();
    Solution solution = Solution(custoBest, solucaoBest, time, alpha);

    return solution;
}

bool Graph::verificaSolucao(vector< int >solucao)
{
    //percorrer todas as arestas verificando se uma das extremidades está na solução
    bool encontrou = false;

    for(Node* no = this->primeiroNo; no != nullptr ; no = no->getProxNo()){
        for(Edge* aux = no->getPrimeiraAresta(); aux != nullptr; aux = aux->getProxAresta()){
            encontrou=false;
            for(int i=0; i < solucao.size(); i++){
                if(aux->getIdCabeca() == solucao[i] || aux->getIdCauda() == solucao[i]){
                    encontrou = true; 
                    break;
                }
            }
            if(!encontrou){ // solucao incorreta
                cout << "não encontrou a aresta:" << aux->getIdCauda() << ", " << aux->getIdCabeca() << endl;  
                return false;
            }
        }
    }

    return true;
}

void Graph::inicializaVetores(vector<float>& probabilidades, vector<float>& medias, vector<int>& aparicoes,  int m)
{
    for(int i = 0; i < m; i ++)
    {
        probabilidades.push_back(1 / (float) m);
        medias.push_back(1);
        aparicoes.push_back(0);
    }
}

void Graph::atualizaProbabilidades(vector<float>& probabilidades, vector<float> medias, float* alpha, Solution solBest)
{
    vector<float> qualidades;
    float somatorio = 0;
    for(int i = 0; i < probabilidades.size(); i++){
        qualidades.push_back(solBest.getCustoTotal()/medias[i]);
        somatorio += qualidades[i];
    }
    for(int i = 0; i < probabilidades.size(); i++){
        if(somatorio != 0){
            probabilidades[i] = qualidades[i]/somatorio;
        }else{
            probabilidades[i] = qualidades[i];
        }
    }
}

int Graph::escolheAlfa(vector<float> probabilidades)
{
    float numeroAleatorio = rand()/(RAND_MAX + 1.0);
    float probabilidadeAcumulada = 0;
    int indiceEscolhido;

    for (int i = 0; i < probabilidades.size(); i++) {
        probabilidadeAcumulada += probabilidades[i];
        if (probabilidadeAcumulada >= numeroAleatorio) {
            indiceEscolhido = i;
            break;
        }
    }
    return indiceEscolhido;
}

void Graph::atualizaMedias(vector<float>& medias, vector<int> aparicoes, int indiceEscolhido, Solution sol )
{
    medias[indiceEscolhido] = (medias[indiceEscolhido] * aparicoes[indiceEscolhido] + sol.getCustoTotal())/(aparicoes[indiceEscolhido] + 1);
}

Solution Graph::coberturaMinimaGulosaRandomizadaReativa(float* alpha, int tamanhoVetor, int nIteracoes, int bloco)
{
    Solution solBest, sol;
    int i = 1;
    vector<float> probabilidades, medias;
    vector<int> aparicoes;
    inicializaVetores(probabilidades, medias, aparicoes, tamanhoVetor);
    high_resolution_clock::time_point start = high_resolution_clock::now();
    double time = 0;

    for(int i = 0; i < tamanhoVetor; i++){
        sol = coberturaMinimaGulosaRandomizada(alpha[i], 1);
        medias[i] = sol.getCustoTotal();
        aparicoes[i] = 1;

        if(i == 0 || solBest.getCustoTotal() > sol.getCustoTotal())
        {
            solBest = sol;
        }
    }

   while(i < nIteracoes){
        if(i % bloco == 0){
            atualizaProbabilidades(probabilidades, medias, alpha, solBest);
        }
        int indiceEscolhido = escolheAlfa(probabilidades);
        float alfaAtual = alpha[ indiceEscolhido ];
        
        sol = coberturaMinimaGulosaRandomizada(alfaAtual, 1);

        atualizaMedias(medias, aparicoes, indiceEscolhido, sol);
        aparicoes[indiceEscolhido] = aparicoes[indiceEscolhido] + 1;

        if(sol.getCustoTotal() < solBest.getCustoTotal() || i == 1)
        {
            solBest = sol;
        }
        i++;
   }


    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop - start).count();
    solBest.setTempoExecucao(time);

   return solBest;
}
