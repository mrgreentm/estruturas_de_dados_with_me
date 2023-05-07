#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/pilha.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void printaVetor(int v[], int tamanhoVetor)
{
    for (int i = 0; i < tamanhoVetor; i++)
    {
        printf("%d\n", v[i]);
    }
}

int converteCharParaInteiro(char numero)
{
    return numero - '0';
}

int achaMenorElementoPilha(Stack *pilha)
{
    if (empty(pilha))
    {
        printf("A pilha está vazia.\n");
        return 0;
    }

    Stack PilhaAuxiliar = *pilha;
    PilhaAuxiliar.top = pilha->top;
    int menor = 10;

    while (!empty(&PilhaAuxiliar))
    {
        char elemento = converteCharParaInteiro(pop(&PilhaAuxiliar));
        if (elemento < menor)
        {
            menor = elemento;
        }
    }
    return menor;
}

void removeMenorElementoDaPilha(Stack *pilha)
{
    int menor = achaMenorElementoPilha(pilha);
    printf("\nmenor:%d", menor);
    int tamanhoRemocao = 0;
    int elemento, i = 0;
    Stack PilhaAuxiliar;
    PilhaAuxiliar.top = -1;
    while (!empty(pilha))
    {
        elemento = converteCharParaInteiro(pop(pilha));
        if (elemento != menor)
            push(&PilhaAuxiliar, elemento);
    }

    while (!empty(&PilhaAuxiliar))
    {
        elemento = pop(&PilhaAuxiliar);
        printf("\nelemento:%d", elemento);
        push(pilha, elemento);
    }
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

void empilhar(Stack *p, char number[])
{
    for (int i = 0; i < strlen(number); i++)
        push(p, number[i]);
}

int main()
{
    Stack pilha_inteiros, pilha_fracionarios;
    pilha_inteiros.top = -1;
    pilha_fracionarios.top = -1;
    int k, w;
    double number;
    char parteFracionariaComoString[MAX_SIZE];
    char parteInteiraComoString[MAX_SIZE];
    printf("Digite, respectivamente, os valores para K e W\n");
    scanf("%d %d", &k, &w);
    printf("Digite o numero desejado (DEVE SER NECESSARIAMENTE UM NUMERO FRACIONARIO)\n");
    scanf("%lf", &number);

    capturarParteFracionaria(number, parteFracionariaComoString);
    capturarParteInteira(number, parteInteiraComoString);

    empilhar(&pilha_inteiros, parteInteiraComoString);
    empilhar(&pilha_fracionarios, parteFracionariaComoString);

    removeMenorElementoDaPilha(&pilha_inteiros);
    return 0;
}
// gcc -o a exercicio_pilha.c ./utils/pilha.c -lm