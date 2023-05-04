#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/pilha.h"
#include <string.h>
#include <math.h>

void split_number(double number)
{
    printf("%lf", ceil(number));
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

    return 0;
}
// gcc -o a exercicio_pilha.c ./utils/pilha.c -lm