#ifndef PILHA_H
#define PILHA_H
#include <string.h>
#include <stdio.h>

typedef struct
{
    int top;
    char items[100];
} Stack;

int empty(Stack *ps);
char pop(Stack *ps);
void push(Stack *ps, char n);
int length(Stack *ps);
int stacktop(Stack *ps);
void popAndTest(Stack *ps, char *px, int *pund);

#endif