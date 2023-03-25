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
    Stack operand;
    Stack operators;
    operand.top = -1;
    operators.top = -1;
    int posfixLength = 0;
    int infixLength = strlen(infix);

    for (int i = 0; i < infixLength; i++) {
        if (isOperand(infix[i])) {
            posfix[posfixLength++] = infix[i];
        } else if (infix[i] == '(') {
            push(&operators, infix[i]);
        } else if (infix[i] == ')') {
            while (!empty(&operators) && operators.items[operators.top] != '(') {
                posfix[posfixLength++] = pop(&operators);
            }

            if (!empty(&operators) && operators.items[operators.top] == '(') {
                pop(&operators);
            }
        } else {
            while (!empty(&operators) && hasPrecedence(operators.items[operators.top], infix[i])) {
                posfix[posfixLength++] = pop(&operators);
            }

            push(&operators, infix[i]);
        }
    }

    while (!empty(&operators)) {
        posfix[posfixLength++] = pop(&operators);
    }

    posfix[posfixLength] = '\0';
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
