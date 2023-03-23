#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "./utils/pilha.h"

#define MAXCOLS 80

bool isOperand(char c)
{
    // isdigit verifica se o caracter é um dígito
    // isalpha verfica se o caracter é uma letra

    if (isdigit(c) || isalpha(c))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int returnPrecedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
}

bool hasPrecedence(char operator_1, char operator_2)
{
    int precedenceOperator_1 = returnPrecedence(operator_1);
    int precedenceOperator_2 = returnPrecedence(operator_2);

    if (precedenceOperator_1 >= precedenceOperator_2){
        return true;
    }
    else{
        return false;
    }
}

int infixToPosfix(){}

int main()
{
    char infix_expression[MAXCOLS];
    char posfix_expression[MAXCOLS];
    int position = 0;
    
    // calculando o tamanho da expressão
    while((infix_expression[position++]) = getchar() != '\n')
    infix_expression[--position] = '\0';
    printf("%s%s", "infixa: ", infix_expression);
    infixToPosfix(infix_expression, posfix_expression);
    printf("\n%s%s", "posfixa: ", posfix_expression);

    printf("%i", hasPrecedence('-', '*'));

    return 0;
}