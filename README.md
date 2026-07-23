#Sistema de Navegação Urbana com Dijkstra e Min-Heap

Este projeto implementa um sistema de navegação urbana (GPS) desenvolvido em **C**, utilizando o **Algoritmo de Dijkstra** otimizado com uma **Min-Heap (Fila de Prioridade)** para calcular o caminho de menor custo entre dois pontos de uma cidade.

A cidade é representada por um **grafo** em forma de grid 10×10 (100 vértices), no qual cada vértice representa um cruzamento e cada aresta representa uma rua com um custo associado ao tempo de deslocamento. Os pesos das ruas simulam diferentes condições de tráfego, incluindo avenidas rápidas e regiões com congestionamento.

Para otimizar o uso de memória, o grafo é implementado utilizando **listas de adjacência**, enquanto a **Min-Heap** permite reduzir a complexidade da seleção do próximo vértice a ser processado durante a execução do algoritmo de Dijkstra.

## Funcionalidades

* Geração automática de um mapa urbano em formato de grid 10×10.
* Representação do mapa utilizando grafos e listas de adjacência.
* Definição de pesos que simulam diferentes condições de trânsito.
* Cálculo da rota de menor custo entre dois vértices utilizando o Algoritmo de Dijkstra.
* Otimização da busca por meio de uma Min-Heap (Fila de Prioridade).

## Tecnologias e Conceitos

* Linguagem C
* Grafos
* Listas Encadeadas
* Listas de Adjacência
* Algoritmo de Dijkstra
* Min-Heap (Binary Heap)
* Filas de Prioridade
* Estruturas Dinâmicas de Dados

## Objetivo

Este projeto foi desenvolvido com fins acadêmicos para aplicar conceitos de **Estruturas de Dados** e **Algoritmos**, demonstrando como grafos e filas de prioridade podem ser utilizados para resolver problemas de roteamento de forma eficiente.
