#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/pilha.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void imprimirPilha(Stack *p)
{
    Stack pilhaAuxiliar = *p;
    pilhaAuxiliar.top = p->top;
    while (!empty(&pilhaAuxiliar))
        printf("%d", pop(&pilhaAuxiliar));
}

void concatenarValoresExibirResultado(Stack *p1, Stack *p2)
{
    printf("Maior valor: ");
    imprimirPilha(p1);
    printf(".");
    imprimirPilha(p2);
}

void ordenarPilha(Stack *pilha)
{
    Stack pilhaAuxiliar;
    pilhaAuxiliar.top = -1;

    while (!empty(pilha))
    {
        char elemento = pop(pilha);
        while (!empty(&pilhaAuxiliar) && stacktop(&pilhaAuxiliar) < elemento)
            push(pilha, pop(&pilhaAuxiliar));

        push(&pilhaAuxiliar, elemento);
    }

    while (!empty(&pilhaAuxiliar))
        push(pilha, pop(&pilhaAuxiliar));
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

    Stack pilhaAuxiliar = *pilha;
    pilhaAuxiliar.top = pilha->top;

    int menor = 10;

    while (!empty(&pilhaAuxiliar))
    {
        int elemento = converteCharParaInteiro(pop(&pilhaAuxiliar));
        printf("# elemento: %d\n", elemento);
        if (elemento < menor)
            menor = elemento;
    }
    printf("menor: %d\n", menor);
    return menor;
}

void removeMenorElementoDaPilha(Stack *pilha, int menor)
{
    printf("MMmenor: %d\n", menor);
    int elemento, i = 0;
    Stack pilhaAuxiliar;
    pilhaAuxiliar.top = -1;
    while (!empty(pilha))
    {
        elemento = converteCharParaInteiro(pop(pilha));

        if (elemento == menor && i > 0)
            push(&pilhaAuxiliar, elemento);
        if (elemento == menor && i == 0)
            i++;
        if (elemento != menor)
            push(&pilhaAuxiliar, elemento);
    }

    while (!empty(&pilhaAuxiliar))
    {
        elemento = pop(&pilhaAuxiliar);
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
    Stack pilha_inteiros, pilha_fracionarios, pilha_auxiliar_inteiros, pilha_auxiliar_fracionarios;
    pilha_inteiros.top = -1;
    pilha_fracionarios.top = -1;
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

    empilhar(&pilha_inteiros, parteInteiraComoString);
    empilhar(&pilha_fracionarios, parteFracionariaComoString);

    for (int i = 0; i < k; i++)
    {
        pilha_auxiliar_inteiros = pilha_inteiros;
        pilha_auxiliar_inteiros.top = pilha_inteiros.top;
        menor = achaMenorElementoPilha(&pilha_auxiliar_inteiros);
        removeMenorElementoDaPilha(&pilha_auxiliar_inteiros, menor);
    }
    for (int j = 0; j < w; j++)
    {
        pilha_auxiliar_fracionarios = pilha_fracionarios;
        pilha_auxiliar_fracionarios.top = pilha_fracionarios.top;
        menor = achaMenorElementoPilha(&pilha_auxiliar_fracionarios);
        removeMenorElementoDaPilha(&pilha_auxiliar_fracionarios, menor);
    }

    ordenarPilha(&pilha_auxiliar_fracionarios);
    ordenarPilha(&pilha_auxiliar_inteiros);

    concatenarValoresExibirResultado(&pilha_auxiliar_inteiros, &pilha_auxiliar_fracionarios);

    return 0;
}
// gcc -o a exercicio_pilha.c ./utils/pilha.c -lm