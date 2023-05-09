#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct no
{
    int dado;
    struct no *proximo;
} No;

typedef struct pilha
{
    No *topo;
} Pilha;

Pilha *criarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

bool pilhaVazia(Pilha *pilha)
{
    return (pilha->topo == NULL);
}

void empilhar(Pilha *pilha, char valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

int desempilhar(Pilha *pilha)
{
    if (pilhaVazia(pilha))
    {
        printf("Erro: a pilha está vazia.\n");
        exit(EXIT_FAILURE);
    }

    int valorDesempilhado = pilha->topo->dado;
    No *noDesempilhado = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(noDesempilhado);
    return valorDesempilhado;
}

int topo(Pilha *pilha)
{
    if (pilhaVazia(pilha))
    {
        printf("Erro: a pilha está vazia.\n");
        exit(EXIT_FAILURE);
    }

    return pilha->topo->dado;
}

int achaMenorElementoPilha(Pilha *pilha)
{
    if (pilhaVazia(pilha))
    {
        printf("Erro: a pilha está vazia.\n");
        exit(EXIT_FAILURE);
    }

    Pilha *pilhaAux = criarPilha();
    int menorElemento = topo(pilha);

    while (!pilhaVazia(pilha))
    {
        int elementoAtual = desempilhar(pilha);
        empilhar(pilhaAux, elementoAtual);

        if (elementoAtual < menorElemento)
        {
            menorElemento = elementoAtual;
        }
    }

    while (!pilhaVazia(pilhaAux))
    {
        int elementoAtual = desempilhar(pilhaAux);
        empilhar(pilha, elementoAtual);
    }

    free(pilhaAux);
    return menorElemento;
}
void concatenarValoresExibirResultado(Pilha *pilha1, Pilha *pilha2)
{
    Pilha *pilhaAux = criarPilha();
    printf("Maior valor: ");

    // Esvazia a primeira pilha, empilhando os elementos na pilha auxiliar
    while (!pilhaVazia(pilha1))
    {
        int elemento = desempilhar(pilha1);
        empilhar(pilhaAux, elemento);
    }

    // Esvazia a segunda pilha, empilhando os elementos na pilha auxiliar
    while (!pilhaVazia(pilha2))
    {
        int elemento = desempilhar(pilha2);
        empilhar(pilhaAux, elemento);
    }

    // Esvazia a pilha auxiliar, exibindo os elementos concatenados
    while (!pilhaVazia(pilhaAux))
    {
        int elemento = desempilhar(pilhaAux);
        printf("%d", elemento);
    }

    printf(".\n");

    free(pilhaAux);
}

void ordenarPilha(Pilha *pilha)
{
    Pilha *pilhaAux = criarPilha();

    while (!pilhaVazia(pilha))
    {
        int elemento = desempilhar(pilha);

        // Desempilha os elementos da pilha auxiliar e empilha na pilha original,
        // enquanto o elemento atual for menor que o elemento do topo da pilha auxiliar
        while (!pilhaVazia(pilhaAux) && elemento < topo(pilhaAux))
        {
            int elementoAux = desempilhar(pilhaAux);
            empilhar(pilha, elementoAux);
        }

        // Empilha o elemento atual na pilha auxiliar
        empilhar(pilhaAux, elemento);
    }

    // Desempilha os elementos da pilha auxiliar e empilha na pilha original,
    // garantindo que a pilha esteja ordenada em ordem crescente
    while (!pilhaVazia(pilhaAux))
    {
        int elemento = desempilhar(pilhaAux);
        empilhar(pilha, elemento);
    }

    free(pilhaAux);
}

int converteCharParaInteiro(char numero)
{
    return numero - '0';
}


void removeMenorElementoDaPilha(Pilha *pilha, int menor, Pilha *pilhaAuxiliar)
{
    int elemento, i = 0;

    while (!pilhaVazia(pilha))
    {
        elemento = desempilhar(pilha);

        if (elemento == menor && i > 0)
            empilhar(pilhaAuxiliar, elemento);
        if (elemento == menor && i == 0)
            i++;
        if (elemento != menor)
            empilhar(pilhaAuxiliar, elemento);
    }

    while (!pilhaVazia(pilhaAuxiliar))
    {
        elemento = desempilhar(pilhaAuxiliar);
        empilhar(pilha, elemento);
    }
    // Libera a memória alocada pela pilha auxiliar
    free(pilhaAuxiliar);
}

void capturarParteFracionaria(double number, char parteFracionariaComoString[])
{
    char buffer[MAX_SIZE];
    int j = 0;
    sprintf(buffer, "%.16g", number);
    char *stringQuebrada = strchr(buffer, '.');
    for (int i = 1; i < strlen(stringQuebrada); i++)
    {
        parteFracionariaComoString[j] = stringQuebrada[i];
        j++;
    }
}
void capturarParteInteira(double number, char parteInteiraComoString[])
{
    int parteInteira = (int)number;
    char buffer[MAX_SIZE];
    int j = 0;
    sprintf(buffer, "%d", parteInteira);
    for (int i = 0; i < strlen(buffer); i++)
    {
        parteInteiraComoString[j] = buffer[i];
        j++;
    }
}

void empilharString(Pilha *p, char number[])
{
    for (int i = 0; i < strlen(number); i++)
        empilhar(p, number[i]);
}

int main()
{
    Pilha *pilha_inteiros = criarPilha(), *pilha_fracionarios = criarPilha(), *pilha_auxiliar_inteiros = criarPilha(), *pilha_auxiliar_fracionarios = criarPilha();
    int k, w, menor = 10;
    double number;
    char parteFracionariaComoString[MAX_SIZE];
    char parteInteiraComoString[MAX_SIZE];
    printf("Digite, respectivamente, os valores para K e W\n");
    scanf("%d %d", &k, &w);
    printf("Digite o numero desejado (DEVE SER NECESSARIAMENTE UM NUMERO FRACIONARIO)\n");
    scanf("%lf", &number);

    capturarParteFracionaria(number, parteFracionariaComoString);
    capturarParteInteira(number, parteInteiraComoString);

    empilharString(pilha_inteiros, parteInteiraComoString);
    empilharString(pilha_fracionarios, parteFracionariaComoString);
    for (int i = 0; i < k; i++)
    {
        menor = achaMenorElementoPilha(pilha_inteiros);
        removeMenorElementoDaPilha(pilha_inteiros, menor, pilha_auxiliar_inteiros);
    }
    for (int j = 0; j < w; j++)
    {

        menor = achaMenorElementoPilha(pilha_fracionarios);
        removeMenorElementoDaPilha(pilha_fracionarios, menor, pilha_auxiliar_fracionarios);
    }

    ordenarPilha(pilha_fracionarios);
    ordenarPilha(pilha_inteiros);

    concatenarValoresExibirResultado(pilha_inteiros, pilha_fracionarios);

    return 0;
}
// gcc -o a exercicio_pilha.c ./utils/pilha.c -lm
