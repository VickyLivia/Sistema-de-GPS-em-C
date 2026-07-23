#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define MAX_VERTICES 100 // Tamanho da cidade (Grid 10x10)
#define INFINITO INT_MAX

//Nó na lista de adjacência (Aresta)
typedef struct Node {
    int destino;
    int peso;
    struct Node* prox;
} Node;

//Grafo
typedef struct Graph {
    int numVertices;
    Node* listasAdj[MAX_VERTICES];
} Graph;

//Min-Heap
typedef struct HeapNode {
    int v;      // Índice do vértice
    int dist;   // Distância acumulada (prioridade)
} HeapNode;

// Estrutura da Min-Heap
typedef struct MinHeap {
    int tamanho;
    int capacidade;
    int *pos;     // Mapa para rastrear posição do vértice no array da heap (Opcional, mas recomendado para decreaseKey)
    HeapNode **array;
} MinHeap;


Graph* criarGrafo(int V);

void adicionarAresta(Graph* graph, int src, int dest, int peso);

void imprimirCaminho(int parent[], int j);

void dijkstra(Graph* graph, int src, int dest);



// Protótipos das funções que VOCÊS devem implementar:

MinHeap* criarMinHeap(int capacidade);

void minHeapify(MinHeap* minHeap, int idx);

HeapNode* extractMin(MinHeap* minHeap);

void decreaseKey(MinHeap* minHeap, int v, int dist);

int isInMinHeap(MinHeap* minHeap, int v);