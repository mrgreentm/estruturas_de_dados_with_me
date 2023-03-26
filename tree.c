#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char inf;
    struct no *filho;
    struct no *irmao;
} no;

no *criarNo(char inf) {
    no *novo_no = (no *) malloc(sizeof(no));
    novo_no->inf = inf;
    novo_no->filho = NULL;
    novo_no->irmao = NULL;
    return novo_no;
}

void adicionarFilho(no *pai, no *filho) {
    if (pai->filho == NULL) {
        pai->filho = filho;
    } else {
        no *atual = pai->filho;
        while (atual->irmao != NULL) {
            atual = atual->irmao;
        }
        atual->irmao = filho;
    }
}

void imprimirArvore(no *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        printf("\t");
    }
    printf("%c", raiz->inf);
    if (raiz->filho != NULL) {
        printf(" (");
        imprimirArvore(raiz->filho, nivel + 1);
        printf("\n");
        for (int i = 0; i < nivel; i++) {
            printf("\t");
        }
        printf(")");
    }
    imprimirArvore(raiz->irmao, nivel);
}

int main() {
    // Criar a raiz da árvore
    no *raiz = criarNo('A');

    // Criar alguns nós filhos
    no *filho1 = criarNo('B');
    no *filho2 = criarNo('C');
    no *filho3 = criarNo('D');
    no *filho4 = criarNo('E');

    // Adicionar os nós filhos à raiz
    adicionarFilho(raiz, filho1);
    adicionarFilho(raiz, filho2);
    adicionarFilho(raiz, filho3);

    // Adicionar um filho ao filho1
    adicionarFilho(filho1, filho4);

    // Imprimir a árvore a partir da raiz
    imprimirArvore(raiz, 0);

    return 0;
}