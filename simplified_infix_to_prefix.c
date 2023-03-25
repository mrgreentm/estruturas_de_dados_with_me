#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/pilha.h"
#include <string.h>

#define MAXCOLS 80

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
        default: return 0;
    }
}

bool hasPrecedence(char operator1, char operator2)
{
    int precedence1 = getPrecedence(operator1);
    int precedence2 = getPrecedence(operator2);
    return precedence1 >= precedence2;
}

void infixToPrefix(char infix[], char prefix[]) {
    Stack operatorStack;
    operatorStack.top = -1;
    Stack operandStack;
    operandStack.top = -1;
    int prefixLength = 0;

    for (int i = strlen(infix) - 1; i >= 0; i--) {
        char symbol = infix[i];

        if (!isOperand(symbol) && hasPrecedence(operatorStack.items[operatorStack.top], symbol)) {
            prefix[prefixLength++] = symbol;
        } else {
            push(&operandStack, symbol);
        }
    }

    while (!empty(&operandStack)) {
        char topSymbol = pop(&operandStack);
        prefix[prefixLength++] = topSymbol;
    }

    prefix[prefixLength] = '\0';

    for (int i = 0; i < prefixLength / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[prefixLength - i - 1];
        prefix[prefixLength - i - 1] = temp;
    }
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