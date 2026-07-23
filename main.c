#include "function.h"

int main() {
    srand(time(NULL));
    // Criação de uma "Manhattan" artificial 10x10 (100 vértices)
    // Vértices são numerados de 0 a 99.
    int V = 100;
    Graph* cidade = criarGrafo(V);

    for (int i = 0; i < 100; i++) {
        int linha = i / 10;
        int coluna = i % 10;

        // linha
        if (coluna < 9) {
            int peso = (rand() % 10) + 1;
            if (linha == 2 || linha == 7)
                peso = 1;

            adicionarAresta(cidade, i, i + 1, peso);
        }

        // vertical
        if (linha < 9) {
            int peso = (rand() % 10) + 1;
            if (coluna == 4 || coluna == 5)
                peso = 20;

            adicionarAresta(cidade, i, i + 10, peso);
        }
    }

    printf("=== SISTEMA DE GPS DE GRAPH CITY ===\n");

    printf("Mapa carregado: 100 cruzamentos (Grade 10x10)\n");

    imprimirCidade(cidade,10);

    //debug
    for (int i = 0; i < 100; i++) {
        printf("%d ->", i);
        Node* aux = cidade->listasAdj[i];
        while (aux) {
            printf(" %d", aux->destino);
            aux = aux->prox;
        }
        printf("\n");
    }




    // Teste 1: Canto superior esquerdo para inferior direito
    // Deve contornar as colunas congestionadas 4 e 5
    dijkstra(cidade, 0, 99); 


    // Teste 2: Rota curta
    dijkstra(cidade, 5, 25);


    return 0;

} 