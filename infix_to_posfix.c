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

void infixToPosfix(char infix[], char posfix[])
{
    int position = 0, outPosition = 0;
    char symbol, topSymbol;
    bool underflow;
    Stack operatorStack;
    operatorStack.top = -1;

    while ((symbol = infix[position++]) != '\0')
    {
        if (isOperand(symbol))
        {
            posfix[outPosition++] = symbol;
        }
        else if (symbol == '(')
        {
            push(&operatorStack, symbol);
        }
        else if (symbol == ')')
        {
            while (!empty(&operatorStack) && operatorStack.items[operatorStack.top] != '(')
            {
                topSymbol = pop(&operatorStack);
                posfix[outPosition++] = topSymbol;
            }

            if (!empty(&operatorStack) && operatorStack.items[operatorStack.top] == '(')
            {
                pop(&operatorStack);
            }
        }
        else
        {
            while (!empty(&operatorStack) && hasPrecedence(operatorStack.items[operatorStack.top], symbol))
            {
                topSymbol = pop(&operatorStack);
                posfix[outPosition++] = topSymbol;
            }

            push(&operatorStack, symbol);
        }
    }

    while (!empty(&operatorStack))
    {
        topSymbol = pop(&operatorStack);
        posfix[outPosition++] = topSymbol;
    }

    posfix[outPosition] = '\0';
}

int main()
{
    char infix[MAXCOLS];
    char posfix[MAXCOLS];

    printf("Digite a expressao infix: ");
    fgets(infix, MAXCOLS, stdin);

    infixToPosfix(infix, posfix);

    printf("Expressao posfixa: %s\n", posfix);

    return 0;
}
