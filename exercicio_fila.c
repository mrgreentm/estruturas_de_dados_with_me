#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int ehUmNumeroOuContemNumero(char* input) {
    int i, len = strlen(input);
    int contains_number = 0;
    for (i = 0; i < len; i++) {
        if (isdigit(input[i])) {
            contains_number = 1;
        } else if (i == 0) {
            return 0;
        }
    }
    return contains_number;
}

#define TAM_MAX 10

typedef struct
{
    char nomes[TAM_MAX][50];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;

void inicializarFila(FilaEstatica *fila)
{
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    for (int i = 0; i < TAM_MAX; i++)
    {
        strcpy(fila->nomes[i], "");
    }
}

void imprimirComEspacos(FilaEstatica fila)
{
    printf("Fila com espaços: ");
    for (int i = 0; i < TAM_MAX; i++)
    {
        if (strcmp(fila.nomes[i], "") == 0)
        {
            printf("- ");
        }
        else
        {
            printf("\033[34m%s \033[0m", fila.nomes[i]);
        }
    }
    printf("\n");
}

void imprimirSemEspacos(FilaEstatica fila)
{
    printf("Fila sem espaços: ");
    for (int i = 0; i < TAM_MAX; i++)
    {
        if (strcmp(fila.nomes[i], "") != 0)
        {
            printf("\033[33m%s\033[0m ", fila.nomes[i]);
        }
    }
    printf("\n");
}

bool filaVazia(FilaEstatica fila)
{
    return (fila.tamanho == 0);
}

bool filaCheia(FilaEstatica fila)
{
    return (fila.tamanho == TAM_MAX);
}

void inserirElemento(FilaEstatica *fila, char nome[])
{
    if (!filaCheia(*fila))
    {
        int i;
        for (i = fila->tamanho - 1; i >= 0 && strcmp(nome, fila->nomes[i]) < 0; i--)
        {
            strcpy(fila->nomes[i + 1], fila->nomes[i]);
        }
        strcpy(fila->nomes[i + 1], nome);
        fila->tamanho++;
        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);
    }
    else
    {
        printf("\033[31mFila cheia, não foi possível inserir o elemento.\033[0m\n");
    }
}

void removerElemento(FilaEstatica *fila)
{
    if (!filaVazia(*fila))
    {
        strcpy(fila->nomes[fila->inicio], "");
        fila->inicio = (fila->inicio + 1) % TAM_MAX;
        fila->tamanho--;
        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);
    }
    else
    {
        printf("\033[31mFila vazia, não foi possível remover um elemento.\033[0m\n");
    }
}
void printarOpcoes()
{
    printf("\033[32m#########################\033[0m");
    printf("\n\033[32m# Sair - 1              #\033[0m\n");
    printf("\033[32m# Inserir - 2           #\033[0m\n");
    printf("\033[32m# Remover - 3           #\033[0m\n");
    printf("\033[32m#########################\033[0m");
    printf("\n");
}
void resetOption(int *option)
{
    *option = 10;
}
int main()
{
    FilaEstatica fila;
    char nome[50];
    inicializarFila(&fila);
    int option = 10;
    printarOpcoes();
    while (option != 0)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Tchauu ;* ");
            exit(1);
            break;
        case 2:
            printf("Digite um nome: ");
            scanf("%s", nome);
            if(ehUmNumeroOuContemNumero(nome)){
                printf("\033[31mDigite um nome válido!!\033[0m\n");
                printarOpcoes();
                break;
            }
            inserirElemento(&fila, nome);
            printarOpcoes();
            resetOption(&option);
            break;
        case 3:
            removerElemento(&fila);
            printarOpcoes();
            resetOption(&option);

        default:
            break;
        }
    }
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
