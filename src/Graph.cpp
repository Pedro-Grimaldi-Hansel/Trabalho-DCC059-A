#include "Graph.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

Graph::Graph(ifstream &arquivoEntrada, bool digrafo, bool ponderadoAresta, bool ponderadoVertice){
    if(!arquivoEntrada.is_open()){
        cout << "ERRO: Arquivo não aberto corretamente!" << endl;
        return;
    }

    this->ultimoIdVinculado = 0;
    this->digrafo = digrafo;
    this->pesoNasArestas = ponderadoAresta;
    this->pesoNosVertices = ponderadoVertice;
    
    string leitor;
    int ordemGrafo;
    int numArestas;
    int idCauda;
    int idCabeca;
    float pesoAresta = 0;

    //Pegar primeira linha e ver o número de nos e arestas
    arquivoEntrada >> ordemGrafo;
    arquivoEntrada >> numArestas;

    cout << "A ordem do grafo é: " << ordemGrafo << endl;
    cout << "o grafo tem " << numArestas << " arestas"<< endl;

    //Primeiro insere todos o vértices
    for(int i = 0; i < ordemGrafo; i++){
        this->insereNoFim(i+1);
    }

    if(ponderadoVertice && !ponderadoAresta){
        //Pegar linha até o fim do arquivo
        while( arquivoEntrada >> leitor >> idCauda >> idCabeca) {
            this->insereAresta(idCauda, idCabeca, pesoAresta);
        }
    }else{
        cout << "ERROR: Leitura ainda não implementada!" << endl;
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
    if(this->pesoNosVertices){
        no->setPesoNo( (idArquivo % 200) + 1);
    }
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

    setNumArestas(getNumArestas()+1);
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

    setNumArestas(getNumArestas()-1);
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
    for(Node* nodeAux = this->primeiroNo; nodeAux != nullptr; nodeAux = nodeAux->getProxNo()){
        if(nodeAux->getIdArquivo() == idArquivo){
            //Estamos no no que queremos deletar
            Node* noASerDecrementado;
            for(Edge* aresta = nodeAux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                noASerDecrementado = buscaNoPorIdArquivo(aresta->getIdCabeca());
                noASerDecrementado->setEntradaNo( noASerDecrementado->getEntradaNo() - 1 );
            }

        }else {
            for(Edge* aresta = nodeAux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                if(aresta->getIdCabeca() ==  idArquivo){
                    nodeAux->removeAresta(idArquivo);

                    if(this->digrafo){
                        //Decrementa o grau de saida
                        nodeAux->setSaidaNo( nodeAux->getSaidaNo() - 1);
                    }else{
                        //Decrementa o grau do no
                        nodeAux->setGrauNo(nodeAux->getGrauNo() - 1);
                    }
                }
            }
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
        cout << "(" << no->getIdArquivo() << ")";
        if(this->pesoNosVertices){
            cout << "<peso: " << no->getPesoNo() << " >";
        }
        cout << endl;
        Edge* aresta = no->getPrimeiraAresta();
        cout << "\t";
        while (aresta != nullptr )
        {
            cout << aresta->getIdCabeca();
            if(this->pesoNasArestas){
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
    else{
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

    while(no != nullptr){ // pegar todas as arestas do grafo e colocar no vetor
        Edge* primeiraAresta = no->getPrimeiraAresta();
        while(primeiraAresta!=nullptr){
            if(this->getDigrafo() || primeiraAresta->getIdCabeca() < no->getIdArquivo()){ // se for digrafo eu tenho q entrar de qqr forma, pois serão duas arestas diferentes msm
                arestas.push_back(*primeiraAresta);// se não for digrafo esse if ajuda a evitar pegar as arestas "duplicadas" que o grafo simples tem
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

    while(contador < numNos-1 && i < arestas.size()){
        int indiceCaudaSubarvores = buscaNoVetor(mapa, arestas[i].getIdCauda(), numNos);
        int indiceCabecaSubarvores = buscaNoVetor(mapa, arestas[i].getIdCabeca(), numNos);

        if(subarvores[indiceCaudaSubarvores] != subarvores[indiceCabecaSubarvores]) // se forem enguais é pq estão na msm subarvores
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
    // vector< int > quantasSubarvoresTem;

    // for(int i=0; i<numNos; i++){
    //     if(buscaNoVector(quantasSubarvoresTem, subarvores[i], quantasSubarvoresTem.size()) == -1){
    //         quantasSubarvoresTem.push_back(subarvores[i]);
    //     }
    // }
    // // depois disso temos como saber o número de subarvores diferentes que existem com o quantasSubarvoresTem.size()
    
    // for(int i=0; i<quantasSubarvoresTem.size(); i++){
    //     for(int j=0; j<AGM.size(); j++){
    //         if(subarvores[j] == i){
    //             print agm[j]
    //         }
    //     }
    // }
    cout << "AGM: {";
    for(int i=0; i<AGM.size(); i++){
        cout << "(" << AGM[i].getIdCauda() << ", " << AGM[i].getIdCabeca() << "), ";
    }
    cout << "}" << endl;

    
}

// atualizar o vetor de subarvores
void Graph::atualizaSubarvores(int numNos, int subarvores[], int indiceCabecaSubarvores, int indiceCaudaSubarvores)
{
    for(int j=0; j<numNos; j++){ 
        if(subarvores[j] == subarvores[indiceCaudaSubarvores]){
            subarvores[j] = subarvores[indiceCabecaSubarvores];
        }
    }
}

int Graph::buscaNoVector(vector< int > vector, int valor, int tam)
{
    for(int i=0; i<tam; i++){
        if(vector[i] == valor){
            return i;
        }
    }
    return -1;
}

int Graph::buscaNoVetor(int vetor[], int idArquivo, int tam)
{
    for(int i=0; i<tam; i++){
        if(vetor[i] == idArquivo){
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

int partition(std::vector<Edge>& vetor, int low, int high) {
    int pivot = vetor[high].getPeso();
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (vetor[j].getPeso() <= pivot) {
            i++;
            std::swap(vetor[i], vetor[j]);
        }
    }

    std::swap(vetor[i + 1], vetor[high]);
    return i + 1;
}

void Graph::quickSort(std::vector<Edge>& vetor, int low, int high) {
    if (low < high) {
        int pi = partition(vetor, low, high);

        quickSort(vetor, low, pi - 1);
        quickSort(vetor, pi + 1, high);
    }
}

// PARTE 2 DO TRABALHO ABAIXO

void Graph::coberturaMinimaGulosa()
{
    // vetor com os nos e graus dos nós
    // contador que começa com o  valor do dobro do número de arestas e é decrementado em 2 a cada aresta adicionada
    // vetor com os nos ordenados por uma ordem de otimidade (custo / grau) que mediria o "quão bom" ele seria para a solução
    // toda vez q colocar alguém na solução é preciso atualizar todos os vetores 
    // vetor solução que vai conter os indices dos nos

    vector< Node > vetorAuxiliar;
    vector< int > solucao;
    float custoTotal = 0;

    for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo())
    {
        if(no->getGrauNo() != 0){
            vetorAuxiliar.push_back(*no);// remover todos os nós com grau 0
        }
    }
    // aqui já temos o vetor auxiliar completo

    while(vetorAuxiliar.size() != 0)
    {
        quickSortGuloso(vetorAuxiliar, 0, vetorAuxiliar.size()-1); // ordenar para ter na primeira posição o "mais ótimo" para a solução
        solucao.push_back(vetorAuxiliar[0].getIdArquivo()); // coloca o "mais ótimo" candidato na solução
        custoTotal += vetorAuxiliar[0].getPesoNo();

        // todo esse for é pra decrementar 1 no grau dos vizinhos do no adicionada à solução
        for(int i = 1; i < vetorAuxiliar.size(); i++){
            for(Edge* aux = vetorAuxiliar[i].getPrimeiraAresta(); aux != nullptr; aux = aux->getProxAresta())
            {
                if(aux->getIdCabeca() == vetorAuxiliar[0].getIdArquivo()){
                    vetorAuxiliar[i].setGrauNo( vetorAuxiliar[i].getGrauNo() - 1); //Atualiza o grau do no
                    if(vetorAuxiliar[i].getGrauNo() == 0){
                        vetorAuxiliar.erase(vetorAuxiliar.begin() + i);// olhuaire de novo isso aqui pq tá estranho
                        i--;
                    }
                }
            }
        }
        // remove o nó que foi  adicionado à solução
        vetorAuxiliar.erase(vetorAuxiliar.begin());   
    }

    // imprimir a solução
    cout << "Tamanho da Solução: " << solucao.size() << " vertices" << endl;
    cout << "Custo total: " << custoTotal << endl;
    cout << endl;
}

// Function to swap two elements
void Graph::swap(Node* a, Node* b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}
 
// Partition the array using the last element as the pivot
int Graph::partitionGuloso(std::vector<Node>& arr, int low, int high)
{
    // Choosing the pivot
    float pivot = arr[high].getPrioridade();
    int desempate = arr[high].getGrauNo();
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j].getPrioridade() < pivot ||( arr[j].getPrioridade() == pivot && arr[j].getGrauNo() > desempate )) {
 
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void Graph::quickSortGuloso(std::vector<Node>& arr, int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = partitionGuloso(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSortGuloso(arr, low, pi - 1);
        quickSortGuloso(arr, pi + 1, high);
    }
}

void Graph::coberturaMinimaGulosaRandomizada(float alpha, int nInteracoes)
{
    vector< Node > vetorAuxiliar;
    vector< int > solucao;
    vector< int > solucaoBest;
    float custoTotal = 0;
    float custoBest = 0;
    //alpha = 0.1; // mais ou menos

    for(int i=0; i<nInteracoes; i++){
        for(Node* no = this->primeiroNo; no != nullptr; no = no->getProxNo())
        {
            if(no->getGrauNo() != 0){
                vetorAuxiliar.push_back(*no);// remover todos os nós com grau 0
            }
        } // aqui já temos o vetor auxiliar completo
        solucao.clear();
        while(vetorAuxiliar.size() > 0)
        {
            quickSortGuloso(vetorAuxiliar, 0, vetorAuxiliar.size()-1); // ordenar para ter na primeira posição o "mais ótimo" para a solução
            solucao.push_back(vetorAuxiliar[0].getIdArquivo()); // coloca o "mais ótimo" candidato na solução
            std::srand(std::time(nullptr));

            int numero_aleatorio = (int)(alpha*(vetorAuxiliar.size()-1));
            if(numero_aleatorio==0)
                numero_aleatorio=1;
            int k = std::rand() % numero_aleatorio; //Randomizao o numero de 0 a alpha*(vetorAuxiliar.size()-1)
            custoTotal += vetorAuxiliar[k].getPesoNo();

            // todo esse for é pra decrementar 1 no grau dos vizinhos do no adicionada à solução
            for(int i = 1; i < vetorAuxiliar.size(); i++){
                for(Edge* aux = vetorAuxiliar[i].getPrimeiraAresta(); aux != nullptr; aux = aux->getProxAresta())
                {
                    if(aux->getIdCabeca() == vetorAuxiliar[k].getIdArquivo()){
                        vetorAuxiliar[i].setGrauNo( vetorAuxiliar[i].getGrauNo() - 1); //Atualiza o grau do no
                        if(vetorAuxiliar[i].getGrauNo() == 0){
                            vetorAuxiliar.erase(vetorAuxiliar.begin() + i);
                            i--;
                        }
                    }
                }
            }
            // remove o nó que foi  adicionado à solução
            vetorAuxiliar.erase(vetorAuxiliar.begin());    
        }

        if(i==0 || custoTotal < custoBest){
           custoBest = custoTotal;
           solucaoBest = solucao; 
        }  //Compara as soluçoes e atualiza a melhor
    }

    bool retorno = verificaSolucao(solucaoBest);
    cout << (retorno ? "A solução é de fato uma das soluções já feitas" : "A solução apresentada está errada") << endl;  

    // imprimir a solução Best
    cout << "Cobertura mínima Guloso Randomizado" << endl;
    cout << "Tamanho da Solução: " << solucaoBest.size() << " vertices" << endl;
    cout << "Custo total: " << custoBest << endl;

}


bool Graph::verificaSolucao(vector< int >solucao)
{
    //percorrer todas as arestas verificando se uma das extremidades está na solução

    for(Node* no = this->primeiroNo; no != nullptr ; no = no->getProxNo()){
        for(Edge* aux = no->getPrimeiraAresta(); aux != nullptr; aux = aux->getProxAresta()){
            bool encontrou = false;
            for(int i=0; i < solucao.size(); i++){
                if(aux->getIdCabeca() == solucao[i] || aux->getIdCauda() == solucao[i]){
                    encontrou = true; 
                    break;
                }
            }
            if(!encontrou){ // solucao incorreta
                return false;
            }
        }
    }

    return true;
}