#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/pilha.h"
#include <string.h>

#define MAXCOLS 80

bool isOperand(char c)
{
    return isalnum(c);
}

int getPrecedence(char operator)
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
    default:
        return 0;
    }
}

bool hasPrecedence(char operator1, char operator2)
{
    int precedence1 = getPrecedence(operator1);
    int precedence2 = getPrecedence(operator2);

    if (precedence1 == 0 && precedence2 == 0)
    {
        return false;
    }

    return precedence1 >= precedence2;
}

void infixToPosFix(char infix[], char posfix[])
{
    Stack operand;
    Stack operators;
    int operandIndex = 0, operatorsIndex = 0, minorPrecedence = 0;
    operand.top = -1;
    operators.top = -1;
    int posfixLength = 0;

    for (int i = 0; i < strlen(infix); i++) // strlen(infix) = tamanho da string infix
    {
        if (isOperand(infix[i]))
        {
            push(&operand,infix[i]);
        }
        if (!isOperand(infix[i]) && hasPrecedence(infix[i], minorPrecedence))
        {
            push(&operand,infix[i]);

        }
        else if (!hasPrecedence(infix[i], minorPrecedence))
        {
            minorPrecedence = infix[i];
        }
    }
    for (int i = 0; i < length(&operand); i++)
    {
        posfix[i] = pop(&operand);
        posfixLength = i;
    }
    for (int i = 0; i < length(&operators); i++)
    {
        posfix[posfixLength++] = pop(&operators);
    }
    printf("\n%s", posfix);
    
    
}

int main()
{
    char infix[MAXCOLS];
    char posfix[MAXCOLS];

    printf("Digite a expressao infix: ");
    fgets(infix, MAXCOLS, stdin);

    infixToPosFix(infix, posfix);

    printf("Expressao posfixa: %s\n", posfix);

    return 0;
}
