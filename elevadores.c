#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>  // Biblioteca necessária para usar a função usleep

#define NUM_ELEVADORES 15    // Total de elevadores
#define NUM_CORREDORES 3     // Total de corredores
#define ANDARES_POR_CORREDOR 10   // Andares em cada corredor

// Estrutura para representar um elevador
typedef struct {
    int id;             // Identificador do elevador
    int posicao;        // Posição atual do elevador
    int destino;        // Próximo destino do elevador
    bool emMovimento;   // Indica se o elevador está em movimento
} Elevador;

// Estrutura para representar um corredor
typedef struct {
    int id;                 // Identificador do corredor
    Elevador elevadores[5]; // Elevadores no corredor
} Corredor;

// Função para inicializar os elevadores
void inicializarElevadores(Corredor corredores[]) {
    int i, j;
    int id = 1;

    for (i = 0; i < NUM_CORREDORES; i++) {
        for (j = 0; j < 5; j++) {
            corredores[i].elevadores[j].id = id++;
            corredores[i].elevadores[j].posicao = 0;
            corredores[i].elevadores[j].destino = 0;
            corredores[i].elevadores[j].emMovimento = false;
        }
    }
}

// Função para encontrar o elevador mais próximo para atender a uma chamada
int encontrarElevadorMaisProximo(Corredor corredores[], int corredor, int destino) {
    int i, j;
    int distanciaMinima = ANDARES_POR_CORREDOR;
    int elevadorMaisProximo = -1;

    for (i = 0; i < NUM_CORREDORES; i++) {
        if (i == corredor) {
            for (j = 0; j < 5; j++) {
                if (!corredores[i].elevadores[j].emMovimento && abs(corredores[i].elevadores[j].posicao - destino) < distanciaMinima) {
                    distanciaMinima = abs(corredores[i].elevadores[j].posicao - destino);
                    elevadorMaisProximo = corredores[i].elevadores[j].id;
                }
            }
        } else {
            for (j = 0; j < 5; j++) {
                if (abs(corredores[i].elevadores[j].posicao - destino) < distanciaMinima) {
                    distanciaMinima = abs(corredores[i].elevadores[j].posicao - destino);
                    elevadorMaisProximo = corredores[i].elevadores[j].id;
                }
            }
        }
    }

    return elevadorMaisProximo;
}

// Função para mover um elevador para o próximo destino
void moverElevador(Corredor corredores[], int corredor, int elevador) {
    if (corredores[corredor].elevadores[elevador].posicao < corredores[corredor].elevadores[elevador].destino) {
        corredores[corredor].elevadores[elevador].posicao++;
    } else if (corredores[corredor].elevadores[elevador].posicao > corredores[corredor].elevadores[elevador].destino) {
        corredores[corredor].elevadores[elevador].posicao--;
    }
}

// Função para exibir a animação dos elevadores
void exibirAnimacao(Corredor corredores[]) {
    system("clear");  // Limpa a tela

    // Loop para exibir o estado dos elevadores em cada andar
    for (int i = ANDARES_POR_CORREDOR - 1; i >= 0; i--) {
        for (int j = 0; j < NUM_CORREDORES; j++) {
            for (int k = 0; k < 5; k++) {
                if (corredores[j].elevadores[k].posicao == i) {
                    printf("[E%d] ", corredores[j].elevadores[k].id);
                } else {
                    printf("     ");
                }
            }
            printf("  ");  // Espaçamento entre os corredores
        }
        printf("\n");
    }
}

int main() {
    Corredor corredores[NUM_CORREDORES];
    int i, j;
    int chamadas[300];  // Vetor para armazenar as chamadas de elevador

    inicializarElevadores(corredores);

    // Simulação das chamadas de elevador
    // Neste exemplo, assume-se que as chamadas são feitas aleatoriamente pelos usuários
    for (i = 0; i < 300; i++) {
        chamadas[i] = rand() % (NUM_CORREDORES * ANDARES_POR_CORREDOR);  // Gera uma chamada aleatória para algum andar do prédio
    }

    // Processamento das chamadas de elevador
    for (i = 0; i < 300; i++) {
        int corredor = chamadas[i] / ANDARES_POR_CORREDOR;  // Determina o corredor da chamada
        int destino = chamadas[i] % ANDARES_POR_CORREDOR;   // Determina o destino da chamada

        int elevadorMaisProximo = encontrarElevadorMaisProximo(corredores, corredor, destino);

        if (elevadorMaisProximo != -1) {
            corredores[corredor].elevadores[elevadorMaisProximo - 1].destino = destino;
            corredores[corredor].elevadores[elevadorMaisProximo - 1].emMovimento = true;
        }

        exibirAnimacao(corredores);  // Exibe a animação atualizada após cada chamada

        usleep(100000);  // Aguarda 500 milissegundos (0.5 segundos) antes de atualizar a animação
    }

    // Simulação do movimento dos elevadores
    for (i = 0; i < ANDARES_POR_CORREDOR; i++) {
        for (j = 0; j < NUM_CORREDORES; j++) {
            for (int k = 0; k < 5; k++) {
                if (corredores[j].elevadores[k].emMovimento) {
                    moverElevador(corredores, j, k);

                    if (corredores[j].elevadores[k].posicao == corredores[j].elevadores[k].destino) {
                        corredores[j].elevadores[k].emMovimento = false;
                    }
                }
            }
        }

        exibirAnimacao(corredores);  // Exibe a animação atualizada após cada movimento de elevador

        usleep(100000);  // Aguarda 500 milissegundos (0.5 segundos) antes de atualizar a animação
    }

    // Impressão do estado final dos elevadores
    for (i = 0; i < NUM_CORREDORES; i++) {
        printf("Corredor %d:\n", i + 1);
        for (j = 0; j < 5; j++) {
            printf("Elevador %d: Posição: %d, Destino: %d\n", corredores[i].elevadores[j].id, corredores[i].elevadores[j].posicao, corredores[i].elevadores[j].destino);
        }
        printf("\n");
    }

    return 0;
}
