#ifndef PILHA_H
#define PILHA_H
#include <string.h> // Inclui a biblioteca GLUT, utilizada para criar a janela e o contexto OpenGL
#include <stdio.h>

typedef struct
{
    int top;
    int items[100];
} Stack;

int empty(Stack *ps);
int pop(Stack *ps);
void push(Stack *ps, int n);
int length(Stack *ps);
int stacktop(Stack *ps);

#endif