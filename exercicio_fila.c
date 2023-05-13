#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_MAX 10

typedef struct {
    char nomes[TAM_MAX][50];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;

void inicializarFila(FilaEstatica *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    for (int i = 0; i < TAM_MAX; i++) {
        strcpy(fila->nomes[i], "");
    }
}

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

void imprimirSemEspacos(FilaEstatica fila) {
    printf("Fila sem espaços: ");
    for (int i = 0; i < TAM_MAX; i++) {
        if (strcmp(fila.nomes[i], "") != 0) {
            printf("%s ", fila.nomes[i]);
        }
    }
    printf("\n");
}

bool filaVazia(FilaEstatica fila) {
    return (fila.tamanho == 0);
}

bool filaCheia(FilaEstatica fila) {
    return (fila.tamanho == TAM_MAX);
}

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
