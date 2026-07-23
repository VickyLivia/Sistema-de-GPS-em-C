#include "function.h"

//Cria e inicializa a Heap vazia

MinHeap* criarMinHeap(int capacidade) {

    MinHeap* retorno = (MinHeap*) malloc(sizeof(MinHeap));

    retorno->capacidade = capacidade;
    retorno->tamanho = 0;

    // Aloca o vetor de posições
    retorno->pos = (int*) malloc(capacidade * sizeof(int));

    // Aloca o vetor de ponteiros para HeapNode
    retorno->array = (HeapNode**) malloc(capacidade * sizeof(HeapNode*));

    return retorno; 
}



//Garante a propriedade de Heap Mínimo no índice idx (Desce o elemento)

void minHeapify(MinHeap* minHeap, int idx)  {

    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    //Verifica o filho da esquerda
    if (esquerda < minHeap->tamanho &&
        minHeap->array[esquerda]->dist < minHeap->array[menor]->dist)
    {
        menor = esquerda;
    }

    // Verifica o filho da direita
    if (direita < minHeap->tamanho &&
        minHeap->array[direita]->dist < minHeap->array[menor]->dist)
    {
        menor = direita;
    }

    //Se encontrou um filho menor, troca
    if (menor != idx) {

        HeapNode *menorNode = minHeap->array[menor];
        HeapNode *idxNode = minHeap->array[idx];

        // Atualiza as posições dos vértices
        minHeap->pos[menorNode->v] = idx;
        minHeap->pos[idxNode->v] = menor;

        // Troca os nós
        minHeap->array[menor] = idxNode;
        minHeap->array[idx] = menorNode;

        // Continua ajustando a heap
        minHeapify(minHeap, menor);
    }
}



//Extrai o nó com menor distância da Heap

HeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->tamanho == 0)
        return NULL;

    HeapNode* retorno = minHeap->array[0];
    HeapNode* ultimo = minHeap->array[minHeap->tamanho - 1];

    minHeap->array[0] = ultimo;
    minHeap->pos[ultimo->v] = 0;

    minHeap->tamanho--;
    minHeap->pos[retorno->v] = minHeap->tamanho;

    minHeapify(minHeap, 0);

    return retorno;
}

//Atualiza a distância de um vértice existente (Sobe o elemento)
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v]; //get onde tal vertice na heap
    int pai = (i - 1) / 2;//só mexo para cima(só da pra diminuir a distancia na heap)

    minHeap->array[i]->dist = dist; //dintancia para somar na heap

    //Enquanto não chegou na raiz e o elemento for menor que o pai
    while (i > 0 && minHeap->array[i]->dist < minHeap->array[pai]->dist){

        // atualizar o vetor pos dos dois vértices
        minHeap->pos[minHeap->array[i]->v] = pai;
        minHeap->pos[minHeap->array[pai]->v] = i;

        //troca
        HeapNode* temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[pai];
        minHeap->array[pai] = temp;

        //continuar a partir da posição do pai
        i = pai;
        pai = (i - 1) / 2;
    }
}




//Verifica se o vértice v está na heap

int isInMinHeap(MinHeap* minHeap, int v) {
    for(int i=0; i<minHeap->tamanho; i++){
        if(v == minHeap->array[i]->v)
            return 1;
    }
    return minHeap->pos[v] < minHeap->tamanho;
}

//Algoritmo Principal

void dijkstra(Graph* graph, int src, int dest) {

    printf("\n--- Calculando rota de %d para %d ---\n", src, dest);

    //inicializa
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];

    for(int i=0; i<MAX_VERTICES; i++){
        dist[i] = INFINITO;
        parent[i] = -1;
    }
    
    MinHeap* minHeap = criarMinHeap(MAX_VERTICES);

    for(int i=0; i < MAX_VERTICES; i++){
        minHeap->array[i] = (HeapNode*) malloc(sizeof(HeapNode)); //decalara direto na heap

        minHeap->array[i]->v = i;
        minHeap->array[i]->dist = dist[i];

        minHeap->pos[i] = i;
    }

    dist[src] = 0;
    minHeap->array[src]->dist = 0;

    minHeap->tamanho = graph->numVertices;

    decreaseKey(minHeap, src, 0);

    while(minHeap->tamanho > 0){
        HeapNode *u = extractMin(minHeap);

        Node *aux = graph->listasAdj[u->v]; //lista

        // Percorre todos os vizinhos de u
        while (aux != NULL) {

            int v = aux->destino;

            // Relaxamento
            if (isInMinHeap(minHeap, v) &&
                dist[u->v] + aux->peso < dist[v]) {

                dist[v] = dist[u->v] + aux->peso;
                parent[v] = u->v; //path

                decreaseKey(minHeap, v, dist[v]);
            }

            aux = aux->prox;
        }
        

    }

    if (dist[dest] == INFINITO) {
        printf("Nao existe caminho.\n");
    }
    else {
        printf("Distancia total: %d\n", dist[dest]);

        printf("Caminho: %d", src);
        imprimirCaminho(parent, dest);
        printf("\n");
    }

}

// Auxiliares
Node* novoNode(int dest, int peso) {

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->destino = dest;

    newNode->peso = peso;

    newNode->prox = NULL;

    return newNode;

}

Graph* criarGrafo(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = V;
    for (int i = 0; i < V; ++i)
        graph->listasAdj[i] = NULL;
    return graph;
}

void adicionarAresta(Graph* graph, int src, int dest, int peso) {

    // Aresta de src para dest
    Node* arestaS = (Node*) malloc(sizeof(Node));
    arestaS->destino = dest;
    arestaS->peso = peso;
    arestaS->prox = graph->listasAdj[src];
    graph->listasAdj[src] = arestaS;

    // Aresta de dest para src (grafo não direcionado)
    Node* arestaD = (Node*) malloc(sizeof(Node));
    arestaD->destino = src;
    arestaD->peso = peso;
    arestaD->prox = graph->listasAdj[dest];
    graph->listasAdj[dest] = arestaD;
}

void imprimirCaminho(int parent[], int j) {
    if (parent[j] == -1)
        return;

    imprimirCaminho(parent, parent[j]);

    printf(" -> %d", j);
}

// printa cidade
int pesoAresta(Graph* g, int u, int v) {
    Node* aux = g->listasAdj[u];

    while (aux != NULL) {
        if (aux->destino == v)
            return aux->peso;
        aux = aux->prox;
    }

    return -1; // não há aresta entre u e v
}

// printa cidade
void imprimirCidade(Graph* g, int size) {

    for (int i = 0; i < size; i++) {

        // NÓS + HORIZONTAIS
        for (int j = 0; j < size; j++) {

            int u = i * size + j;
            printf("(%2d)", u);

            if (j < size - 1) {
                int v = u + 1;
                int peso = pesoAresta(g, u, v);

                printf("---%2d---", peso);
            }
        }

        printf("\n");

        // VERTICAIS
        if (i < size - 1) {

            for (int j = 0; j < size; j++) {

                int u = i * size + j;
                int v = u + size;
                int peso = pesoAresta(g, u, v);

                // Parte de baixo do nó: precisa ter exatamente 4 caracteres,
                // o mesmo tamanho de "(%2d)", para alinhar certinho.
                if (peso == -1)
                    printf("    ");        // sem conexão: 4 espaços
                else
                    printf("|%2d|", peso); // "|" + 2 dígitos + "|" = 4 chars

                // Espaço entre colunas: precisa ter exatamente 8 caracteres,
                // o mesmo tamanho de "---%2d---", já que ali não há info vertical.
                if (j < size - 1)
                    printf("        ");
            }

            printf("\n");
            printf("\n"); // linha em branco extra para respirar
        }
    }
}