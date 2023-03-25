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

void infixToPosFix(char infix[], char posfix[]) {
    Stack operatorStack;
    operatorStack.top = -1;
    int posfixLength = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char symbol = infix[i];

        if (isOperand(symbol)) {
            posfix[posfixLength++] = symbol;
            posfix[posfixLength++] = ' ';
        } else {
            while (!empty(&operatorStack) && hasPrecedence(operatorStack.items[operatorStack.top], symbol)) {
                char topSymbol = pop(&operatorStack);
                posfix[posfixLength++] = topSymbol;
                posfix[posfixLength++] = ' ';
            }
            push(&operatorStack, symbol);
        }
    }

    while (!empty(&operatorStack)) {
        char topSymbol = pop(&operatorStack);
        posfix[posfixLength++] = topSymbol;
        posfix[posfixLength++] = ' ';
    }

    posfix[posfixLength] = '\0';
}

int main()
{
    char infix[MAXCOLS];
    char posfix[MAXCOLS];

    printf("Digite a expressao infix: ");
    fgets(infix, MAXCOLS, stdin);

    char *pch = strchr(infix, ' ');
    while (pch != NULL)
    {
        strncpy(pch, pch + 1, strlen(pch));
        pch = strchr(infix, ' ');
    }

    infixToPosFix(infix, posfix);

    printf("Expressao posfixa: %s\n", posfix);

    return 0;
}
