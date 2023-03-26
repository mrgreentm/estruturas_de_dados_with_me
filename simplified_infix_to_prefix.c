#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "./utils/pilha.h"

#define MAXCOLS 80

void reverse_string(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

bool isOperand(char c)
{
    return islower(c) || isdigit(c);
}

int getPrecedence(char operator)
{
    switch (operator)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '^': return 3;
        default:  return 0;
    }
}

bool hasPrecedence(char operator1, char operator2)
{
    int precedence1 = getPrecedence(operator1);
    int precedence2 = getPrecedence(operator2);
    return precedence1 >= precedence2;
}

void infixToPrefix(char infix[], char prefix[])
{
    Stack operatorStack;
    operatorStack.top = -1;

    int infixExpressionSize = strlen(infix);
    int prefixLength = 0;

    for (int i = infixExpressionSize - 1; i >= 0; i--)
    {
        char symbol = infix[i];

        if (isOperand(symbol))
        {
            prefix[prefixLength++] = symbol;
        }
        else
        {
            while (!empty(&operatorStack) && hasPrecedence(operatorStack.items[operatorStack.top], symbol))
            {
                prefix[prefixLength++] = operatorStack.items[operatorStack.top];
                pop(&operatorStack);
            }
            push(&operatorStack, symbol);
        }
    }

    while (!empty(&operatorStack))
    {
        prefix[prefixLength++] = operatorStack.items[operatorStack.top];
        pop(&operatorStack);
    }

    reverse_string(prefix);

    prefix[prefixLength] = '\0';
}

int main()
{
    char infix[MAXCOLS];
    char prefix[MAXCOLS];

    printf("Digite a expressao infix: ");
    fgets(infix, MAXCOLS, stdin);

    infixToPrefix(infix, prefix);

    printf("Expressao prefixa: %s\n", prefix);
    return 0;
}
