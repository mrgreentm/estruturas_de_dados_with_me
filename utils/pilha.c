#include "pilha.h"
#include <stdio.h>

#define STACK_SIZE 100
#define TRUE 1
#define FALSE 0



// recebe um ponteiro que aponta para a pilha
int empty(Stack *ps)
{
    if (ps->top == -1)
        return (TRUE);
    else
        return (FALSE);
};

int pop(Stack *ps)
{
    if (empty(ps))
    {
        printf("underflow");
        return 0;
    }
    else
    {
        return ps->items[ps->top--]; // retorna e atualiza elemento na posição top
    }
}

void popAndTest(Stack *ps, char *px, int *pund)
{
    if(empty(ps)){
        *pund = TRUE;
        return;
    }
    *pund = FALSE;
    *px = ps->items[ps->top--];
    return;
}

void push(Stack *ps, int n)
{
    if (ps->top == STACK_SIZE - 1)
    {
        printf("stack-overflow");
        return;
    }
    else
    {
        ps->items[++(ps->top)] = n;
        return;
    }
}

int length(Stack *ps)
{
    return ps->top+1;
}

int stacktop(Stack *ps)
{
    if (empty(ps))
    {
        printf("empty stack");
        return 0;
    }
    else
    {
        int x = pop(ps);
        push(ps, x);
        return x;
    }
}

// int main()
// {
//     Stack s;
//     // devemos iniciar o topo com -1 para indicarmos que a pilha está vazia
//     s.top = -1;
//     push(&s, 12);
//     push(&s, 24);
//     push(&s, 1);
//     push(&s, 5);
//     push(&s, 17);
//     push(&s, 51);
//     push(&s, 57);
//     push(&s, 789);

//     printf("\n## %i foi removido ##\n", pop(&s));

//     printf("Tamanho da pilha: %i", length(&s));

//     return 0;
// }