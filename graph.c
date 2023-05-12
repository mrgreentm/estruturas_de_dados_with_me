#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa um nó do grafo
typedef struct node {
    int vertex;               // número do vértice
    struct node* next;        // ponteiro para o próximo nó adjacente
} Node;

// Estrutura que representa o grafo
typedef struct graph {
    int num_vertices;         // número de vértices do grafo
    Node** adj_lists;         // vetor de listas de adjacências
} Graph;

// Função para criar um novo nó do grafo
Node* create_node(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com n vértices
Graph* create_graph(int n) {
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph->num_vertices = n;
    newGraph->adj_lists = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        newGraph->adj_lists[i] = NULL;
    }
    return newGraph;
}

// Função para adicionar uma aresta ao grafo
void add_edge(Graph* g, int src, int dest) {
    // Adiciona a aresta de src para dest
    Node* newNode = create_node(dest);
    newNode->next = g->adj_lists[src];
    g->adj_lists[src] = newNode;

    // Adiciona a aresta de dest para src (grafo não direcionado)
    newNode = create_node(src);
    newNode->next = g->adj_lists[dest];
    g->adj_lists[dest] = newNode;
}

// Função para imprimir o grafo
void print_graph(Graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Adjacências do vértice %d: ", i);
        Node* current = g->adj_lists[i];
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Função principal
int main() {
    Graph* g = create_graph(4);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    print_graph(g);
    return 0;
}