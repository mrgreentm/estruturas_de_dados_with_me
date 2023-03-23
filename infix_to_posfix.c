#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

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
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '^':
        return 3;
        break;
    }
}

int hasPrecedence(char operator_1, char operator_2)
{
    int precedenceOperator_1 = returnPrecedence(operator_1);
    int precedenceOperator_2 = returnPrecedence(operator_2);

    if (precedenceOperator_1 >= precedenceOperator_2){
        return 1;
    }
    else{
        return 0;
    }
}

int main()
{
    printf("%i", hasPrecedence('-', '*'));

    return 0;
}