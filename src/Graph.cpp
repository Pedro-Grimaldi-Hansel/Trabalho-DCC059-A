#include "Graph.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

using namespace std;

Graph::Graph(ifstream &arquivoEntrada){
    if(!arquivoEntrada.is_open()){
        cout << "ERRO: Arquivo não aberto corretamente!" << endl;
        return;
    }

    //Pegar primeira linha e ver o número de nos
    this->ultimoIdVinculado = 0;
    int ordemGrafo;
    int idCauda;
    int idCabeca;
    float peso;

    this->digrafo = false;

    arquivoEntrada >> ordemGrafo;
    cout << "A ordem do grafo é: " << ordemGrafo << endl;

    //Primeiro insere todos o vértices
    for(int i = 0; i < ordemGrafo; i++){
        this->insereNoFim(i+1);
    }

    //Pegar linha até o fim do arquivo
    while( arquivoEntrada >> idCauda >> idCabeca >> peso) {
        this->insereAresta(idCauda, idCabeca, peso);
    }
}

void Graph::escreveArquivo(ofstream &arquivoSaida)
{
    // Verificar se o arquivo foi aberto corretamente
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao abrir o arquivo " << endl;
        return;
    }

    arquivoSaida << this->getOrdem() << endl;

    // Escrever as arestas do grafo
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo()){
        for(Edge* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(no->getIdArquivo() > aresta->getIdCabeca()){
                continue; //Para não repetir aresta
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
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao abrir o arquivo " << endl;
        return;
    }
    
    // Escrever o cabeçalho do arquivo DOT
    if(this->digrafo){
        arquivoSaida << "digraph Grafo {" << endl;
    }else{
        arquivoSaida << "graph Grafo {" << endl;
    }
    
    // Escrever as arestas do grafo
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo()){
        for(Edge* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(no->getIdArquivo() < aresta->getIdCabeca()){
                continue; //Para não repetir aresta
            }
            arquivoSaida << "    " << no->getIdArquivo();
            if(this->digrafo){
                arquivoSaida << " -> ";
            }else{
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

Node* Graph::getPrimeiroNo(){
    return this->primeiroNo;
}

//Somente utilizado para nos já inseridos!
void Graph::vinculaNo(int idArquivo)
{
    Node* no = this->ultimoNoVinculado; //Pega o ultimo no vinculado

    if(no == nullptr){ // Caso o ultimo no vinculado seja null
        this->ultimoNoVinculado = this->primeiroNo; //ultimo no vinculado recebe o primeiro no
    }else{
        this->ultimoNoVinculado = no->getProxNo(); //Atualiza o ultimo nó vinculado
        if(this->ultimoNoVinculado == nullptr){
            printf("Ordem do Grafo ultrapassada! Insira um nó!");
            return;
        }
    }
    no = this->ultimoNoVinculado; //No revebe o ultimo no vinculado
    no->setIdArquivo(idArquivo); //vincula o no
    this->ultimoIdVinculado += 1; //incrementar o ultimo vinculado
}

void Graph::insereNoFim(int id){
    Node* no = new Node(id);
    no->setProxNo(nullptr);

    if(this->primeiroNo == nullptr) //caso o grafo esteja vazio, insere no inicio mesmo
    {
        this->primeiroNo = no;
        this->ultimoNo = no;
    }
    else
    {
        this->ultimoNo->setProxNo(no);
        this->ultimoNo = no;
    }
}

Node* Graph::buscaNoPorIdArquivo(int idArquivo){
    Node* no = this->primeiroNo; //auxiliar para busca

    while (no != nullptr)
    {
        if(no->getIdArquivo() == idArquivo){ //caso encontrou o nó retorna ele
            return no;
        }

        no = no->getProxNo(); //se não encontrou passa para o próximo
    }
    //caso nao tenha encontrado nenhum, retorna nullptr
    return nullptr;
}

void Graph::insereAresta(int idCauda, int idCabeca, float peso){
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr){
        this->vinculaNo(idCauda);
        cauda = this->ultimoNoVinculado;
    }
    if(cabeca == nullptr){
        this->vinculaNo(idCabeca);
        cabeca = this->ultimoNoVinculado;
    }

    cauda->insereAresta(idCabeca, peso);

    if(!this->digrafo){
        cabeca->insereAresta(idCauda, peso);
    }

    if(!this->getDigrafo()){
        cabeca->setGrauNo(cabeca->getGrauNo() + 1);
        cauda->setGrauNo(cauda->getGrauNo() + 1);
    }
    else{
        cabeca->setEntradaNo(cabeca->getEntradaNo() + 1);
        cauda->setSaidaNo(cauda->getSaidaNo() + 1);
    }

    this->numberOfEdges++;
}

void Graph::removeAresta(int idCauda, int idCabeca){
    //busca Nos
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr || cabeca == nullptr){
        cout << "Aresta inexiste" << endl;
        return;
    }
    
    //chama a remoção de aresta do no
    bool removido = cauda->removeAresta(idCabeca);
    if( removido ){
        if(this->digrafo){
            cauda->setSaidaNo(cauda->getSaidaNo() - 1);
        }else{
            cauda->setGrauNo(cauda->getGrauNo() - 1);
        }
    }

    //verifica se o não for digrafo tem que remover a aresta na cabeça também
    if(!this->digrafo){
        removido = cabeca->removeAresta(idCauda);
        if( removido ){
            cabeca->setGrauNo(cabeca->getGrauNo() - 1);
        }
    }

    this->numberOfEdges--;
}

bool Graph::removeNo(int idArquivo){
    Node* no = this->primeiroNo;
    Node* noAnteriror = nullptr;

    if(this->primeiroNo == nullptr){
        cout << "Grafo Vazio!" << endl;
        return false;
    }

    //Percorre todos os nos armazenando o atual e anterior
    while(no != nullptr){
        if(no->getIdArquivo() == idArquivo){
            break; //encontrou a no
        }
        noAnteriror = no;
        no = no->getProxNo();
    }

    //No não encontrada
    if(no == nullptr){
        cout << "No não encotrado!" << endl;
        return false;
    }

    //Remove todas as arestas
    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo()){
        for(Edge* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(aresta->getIdCabeca() ==  idArquivo)
                no->removeAresta(idArquivo);
        }
    }

    if(noAnteriror == nullptr){
        //o no é a primeira da lista
        this->primeiroNo = no->getProxNo();
    }else if(no->getProxNo() == nullptr){
        //o no é a ultima da lista
        noAnteriror->setProxNo(nullptr);
    }else{
        //a no está no meio
        noAnteriror->setProxNo(no->getProxNo());
    }
    
    delete no;
    return true;
}

void Graph::imprime(){
    Node* no =  this->primeiroNo;

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr)
    {
        cout << "(" << no->getIdArquivo() << ")" << endl;
        Edge* aresta = no->getPrimeiraAresta();
        cout << "\t";
        while (aresta != nullptr )
        {
            cout << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
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
    else{
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }

}

/*int Graph::getEntradaNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(getDigrafo())
    {
        return no->getEntradaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }

}

int Graph::getSaidaNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(getDigrafo())
    {
        return no->getSaidaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }
}
*/
bool Graph::getKRegularidade(int k)
{
    Node* no = this->primeiroNo;

    if(no->getGrauNo() != k){
        return false;
    }
    else{
        while (no != nullptr)
        {
            if(no->getGrauNo() != k){ //caso tenha grau diferente de k retorna false
                return false;
            }

            no = no->getProxNo(); //se tinha grau k passa para o próximo
        }
        return true; // se não retornou false depois de passar por todos retorna true
    }
}

int Graph::getOrdem()
{
    Node* no = this->primeiroNo;
    int ordem = 0;

    while (no != nullptr)
    {
        ordem++;
        no = no->getProxNo();
    }
    return ordem;
}

bool Graph::isTrivial()
{
    Node* no = this->primeiroNo;
    
    if(no->getProxNo() == nullptr){ // se o próximo do primeiro for null é pq só possui um no
        return true;
    }
    else{
        return false;
    }
}

bool Graph::isNulo()
{
    Node* no = this->primeiroNo;

    if(no == nullptr){
        return true;
    }
    else{
        return false;
    }
}

int Graph::getGrauGrafo() // não está adaptado para um digrafo 
{
    Node* no = this->primeiroNo;
    int grau = no->getGrauNo();

    while (no != nullptr)
    {
        if(no->getGrauNo() > grau){ //caso tenha grau maior que o anterior, atualiza o valor de grau
            grau = no->getGrauNo();
        }

        no = no->getProxNo(); // passa para o próximo
    }
    return grau; // retorna o maior grau entre os nos do grafo
}

int* Graph::sequenciaDeGraus(){     // não está adaptado para um digrafo
    if (this == nullptr || this->primeiroNo == nullptr || getOrdem() <= 0) {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }

    Node* no = this->primeiroNo;
    int* sequencia=new int[getOrdem()];

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < getOrdem(); i++){
            if (no != nullptr) {
                sequencia[i] = no->getGrauNo();
                no = no->getProxNo();
            } else {
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

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta()){
        vizinhancaAberta.push_back(aresta->getIdCabeca());
    }
    cout << "A vizinhança aberta é: " << endl; 
    for (int i = 0; i < vizinhancaAberta.size(); i++) {
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

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta()){
        vizinhancaFechada.push_back(aresta->getIdCabeca());
    }
    
    cout << "A vizinhança fechada é: " << endl; 
    for (int i = 0; i < vizinhancaFechada.size(); i++) {
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
    return this->numberOfEdges; 
}

bool Graph::isComplete()
{
    int n = getNumberOfNodes();
    int edgesToBeComplete = n*(n-1)/2;
    if(getDigrafo())
    {
        if(getNumberOfEdges() != edgesToBeComplete)
        {
            return false;
        }
        else
        {
            Node* currentNode = getPrimeiroNo();
            while (currentNode != nullptr)
            {
                Node* otherNode = currentNode->getProxNo();
                while (otherNode != nullptr)
                {
                    if (currentNode->buscaAresta(otherNode->getIdArquivo()) == nullptr)
                    {
                        return false;
                    }
                    otherNode = otherNode->getProxNo();
                }
                currentNode = currentNode->getProxNo();
            }
        }
    }
    else
    {
        if (getNumberOfEdges() != edgesToBeComplete)
        {
            return false;
        }

        else
        {
            // Confere se há self-loops ou multiarestas
            Node* currentNode = getPrimeiroNo();
            while (currentNode != nullptr)
            {
                if (currentNode->getGrauNo() != n - 1)
                {
                    return false;
                }
                currentNode = currentNode->getProxNo();
            }
        }
    }
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

        Edge* currentEdge = buscaNoPorIdArquivo(currentNode)->getPrimeiraAresta();

        while (currentEdge != nullptr) 
        {
            int neighborNode = currentEdge->getIdCabeca();

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
                if (!BFSColoring(i, color, visited)) {
                    return false;  // Grafo não é Bipartido
                }
            }
        }

        return true;  // Grafo Bipartido
    }
}

bool Graph::isEulerian()
{

}