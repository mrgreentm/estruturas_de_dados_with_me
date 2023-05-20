#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define WHITE_SPACE " "

int ehUmNumeroOuContemNumero(char *input)
{
    int i, len = strlen(input);
    int contains_number = 0;
    for (i = 0; i < len; i++)
    {
        if (isdigit(input[i]))
        {
            contains_number = 1;
        }
        else if (isspace(input[i]))
        {
            // Se o caractere atual é um espaço em branco, continue verificando
            continue;
        }
        else if (i == 0)
        {
            return 0;
        }
        else
        {
            // Se o caractere atual não é um dígito nem um espaço em branco, retorne falso
            return 0;
        }
    }
    return contains_number;
}

#define TAM_MAX 10

typedef struct
{
    char nomes[TAM_MAX][50];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;

void inicializarFila(FilaEstatica *fila)
{
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    for (int i = 0; i < TAM_MAX; i++)
    {
        strcpy(fila->nomes[i], "");
    }
}

void imprimirComEspacos(FilaEstatica fila)
{
    printf("Fila com espaços: ");
    for (int i = 0; i < TAM_MAX; i++)
    {
        if (strcmp(fila.nomes[i], "") == 0)
        {
            printf("- ");
        }
        else
        {
            printf("\033[34m%s, \033[0m", fila.nomes[i]);
        }
    }
    printf("\n");
}

void imprimirSemEspacos(FilaEstatica fila)
{
    printf("Fila sem espaços: ");
    for (int i = 0; i < TAM_MAX; i++)
    {
        if (strcmp(fila.nomes[i], "") != 0)
        {
            printf("\033[33m%s,\033[0m ", fila.nomes[i]);
        }
    }
    printf("\n");
}

bool filaVazia(FilaEstatica fila)
{
    return (fila.tamanho == 0);
}

bool filaCheia(FilaEstatica fila)
{
    return (fila.tamanho == TAM_MAX);
}

void inserirElemento(FilaEstatica *fila, char nome[])
{
    // Verifica se a fila já contém o nome a ser inserido
    for (int i = 0; i < fila->tamanho; i++)
    {
        if (strcasecmp(nome, fila->nomes[i]) == 0)
        {
            printf("\033[31mO nome '%s' já está na fila.\033[0m\n", nome);
            return;
        }
    }

    if (!filaCheia(*fila))
    {
        // Procura pelo primeiro espaço vazio na fila (indicado pelo hífen)
        int i;
        for (i = 0; i < fila->tamanho; i++)
        {
            if (strcmp(fila->nomes[i], "-") == 0)
            {
                strcpy(fila->nomes[i], nome);
                break;
            }
        }

        // Caso não tenha encontrado um espaço vazio, insere o elemento no final da fila
        if (i == fila->tamanho)
        {
            strcpy(fila->nomes[fila->tamanho], nome);
            fila->tamanho++;
        }

        // Ordena a fila em ordem alfabética
        for (int i = 0; i < fila->tamanho - 1; i++)
        {
            for (int j = i + 1; j < fila->tamanho; j++)
            {
                if (strcasecmp(fila->nomes[i], fila->nomes[j]) > 0)
                {
                    char temp[50];
                    strcpy(temp, fila->nomes[i]);
                    strcpy(fila->nomes[i], fila->nomes[j]);
                    strcpy(fila->nomes[j], temp);
                }
            }
        }

        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);
    }
    else
    {
        printf("\033[31mFila cheia, não foi possível inserir o elemento.\033[0m\n");
    }
}



void removerElemento(FilaEstatica *fila)
{
    if (!filaVazia(*fila))
    {
        // Salva o nome removido para imprimir mais tarde
        char nomeRemovido[50];
        strcpy(nomeRemovido, fila->nomes[0]);

        // Substitui o primeiro elemento removido por um hífen "-"
        strcpy(fila->nomes[0], "-");

        // Imprime a fila atualizada
        imprimirComEspacos(*fila);
        imprimirSemEspacos(*fila);

        printf("\033[32m'%s' removido da fila.\033[0m\n", nomeRemovido);
    }
    else
    {
        printf("\033[31mFila vazia, não foi possível remover um elemento.\033[0m\n");
    }
}


void printarOpcoes()
{
    printf("\033[32m#########################\033[0m");
    printf("\n\033[32m# Sair    - 1           #\033[0m\n");
    printf("\033[32m# Inserir - 2           #\033[0m\n");
    printf("\033[32m# Remover - 3           #\033[0m\n");
    printf("\033[32m#########################\033[0m");
    printf("\n");
}
void resetOption(int *option)
{
    *option = 10;
}
int main()
{
    FilaEstatica fila;
    char nome[50];
    inicializarFila(&fila);
    int option = 10;
    printarOpcoes();
    while (option != 0)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Tchauu ;* ");
            exit(1);
            break;
        case 2:
            printf("Digite um nome: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0'; // remove o caractere de nova linha
            if (ehUmNumeroOuContemNumero(nome) || strlen(nome) < 3 || nome == WHITE_SPACE)
            {
                printf("\033[31mDigite um nome válido!!\033[0m\n");
                printarOpcoes();
                break;
            }
            inserirElemento(&fila, nome);
            printarOpcoes();
            resetOption(&option);
            break;
        case 3:
            removerElemento(&fila);
            printarOpcoes();
            resetOption(&option);
            break;
        default:
            break;
        }
    }

    return 0;
}
