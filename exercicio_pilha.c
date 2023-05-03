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

int main()
{
    Stack p;
    double number;
    char parteFracionariaComoString[MAX_SIZE];
    scanf("%lf", &number);
    capturarParteFracionaria(number, parteFracionariaComoString);

    return 0;
}
