#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_MAX 10 // Tamanho máximo da fila

typedef struct {
    char nomes[TAM_MAX][50];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;

// Função para inicializar a fila
void inicializarFila(FilaEstatica *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    for (int i = 0; i < TAM_MAX; i++) {
        strcpy(fila->nomes[i], "");
    }
}

// Função para imprimir a fila com os espaços
void imprimirComEspacos(FilaEstatica fila) {
    printf("Fila com espaços: ");
    for (int i = 0; i < TAM_MAX; i++) {
        if (strcmp(fila.nomes[i], "") == 0) {
            printf("- ");
        } else {
            printf("%s ", fila.nomes[i]);
        }
    }
    printf("\n");
}

// Função para imprimir a fila sem os espaços
void imprimirSemEspacos(FilaEstatica fila) {
    printf("Fila sem espaços: ");
    for (int i = 0; i < TAM_MAX; i++) {
        if (strcmp(fila.nomes[i], "") != 0) {
            printf("%s ", fila.nomes[i]);
        }
    }
    printf("\n");
}

// Função para verificar se a fila está vazia
bool filaVazia(FilaEstatica fila) {
    return (fila.tamanho == 0);
}

// Função para verificar se a fila está cheia
bool filaCheia(FilaEstatica fila) {
    return (fila.tamanho == TAM_MAX);
}

// Função para inserir um elemento na fila
void inserirElemento(FilaEstatica *fila, char nome[]) {
    if (!filaCheia(*fila)) {
        int i;
        for (i = fila->tamanho - 1; i >= 0 && strcmp(nome, fila->nomes[i]) < 0; i--) {
            strcpy(fila->nomes[i + 1], fila->nomes[i]);
        }
        strcpy(fila->nomes[i + 1], nome);
        fila->tamanho++;
        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);
    } else {
        printf("Fila cheia, não foi possível inserir o elemento.\n");
    }
}

// Função para remover um elemento da fila
void removerElemento(FilaEstatica *fila) {
    if (!filaVazia(*fila)) {
        strcpy(fila->nomes[fila->inicio], "");
        fila->inicio = (fila->inicio + 1) % TAM_MAX;
        fila->tamanho--;
        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);
    } else {
        printf("Fila vazia, não foi possível remover um elemento.\n");
    }
}
int main() {
    FilaEstatica fila;
    inicializarFila(&fila);

    inserirElemento(&fila, "Maria");
    inserirElemento(&fila, "João");
    inserirElemento(&fila, "Pedro");
    inserirElemento(&fila, "Ana");

    removerElemento(&fila);
    removerElemento(&fila);

    inserirElemento(&fila, "Carlos");
    inserirElemento(&fila, "Fernanda");

    return 0;
}
