#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int isOperand(char c) {
    // isdigit verifica se o caracter é um dígito
    // isalpha verfica se o caracter é uma letra

    if (isdigit(c) || isalpha(c)) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    char c;
    scanf("%c", &c);
    printf("%i", isOperand(c));
    return 0;
}