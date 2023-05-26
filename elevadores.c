#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_ELEVADORES 15
#define NUM_CORREDORES 3
#define ANDARES_POR_CORREDOR 100
#define NUM_ANDARES_TOTAL (NUM_CORREDORES * ANDARES_POR_CORREDOR)

typedef struct {
    int id;
    int corredor;
    int andar_atual;
    int em_movimento;
} Elevador;

typedef struct {
    int andar_chamada;
    int corredor_chamada;
} Chamada;

Elevador elevadores[NUM_ELEVADORES];
Chamada chamadas[NUM_ANDARES_TOTAL];

void inicializar_elevadores() {
    int i, j;
    int elevadores_por_corredor = NUM_ELEVADORES / NUM_CORREDORES;
    for (i = 0; i < NUM_CORREDORES; i++) {
        for (j = 0; j < elevadores_por_corredor; j++) {
            int elevador_idx = i * elevadores_por_corredor + j;
            elevadores[elevador_idx].id = elevador_idx + 1;
            elevadores[elevador_idx].corredor = i;
            elevadores[elevador_idx].andar_atual = i * ANDARES_POR_CORREDOR;
            elevadores[elevador_idx].em_movimento = 0;
        }
    }
}

void exibir_estado_elevadores() {
    int i;
    for (i = 0; i < NUM_ELEVADORES; i++) {
        printf("Elevador %d: Corredor %d, Andar %d\n", elevadores[i].id, elevadores[i].corredor, elevadores[i].andar_atual);
    }
    printf("\n");
}

void exibir_chamada(int andar, int corredor) {
    printf("Chamada para Elevador: Corredor %d, Andar %d\n", corredor, andar);
}

int encontrar_elevador_disponivel(int andar_chamada, int corredor_chamada) {
    int i;
    for (i = 0; i < NUM_ELEVADORES; i++) {
        if (!elevadores[i].em_movimento && elevadores[i].corredor == corredor_chamada) {
            return i;
        }
    }
    return -1;
}

int verificar_colisao(int elevador_idx, int destino_andar) {
    int i;
    for (i = 0; i < NUM_ELEVADORES; i++) {
        if (i != elevador_idx && elevadores[i].andar_atual == destino_andar && elevadores[i].em_movimento) {
            return 1;
        }
    }
    return 0;
}

void mover_elevador(int elevador_idx, int destino_andar) {
    int corredor_destino = destino_andar / ANDARES_POR_CORREDOR;

    if (elevadores[elevador_idx].corredor != corredor_destino) {
        printf("Elevador %d: Movendo do Corredor %d para o Corredor %d\n", elevadores[elevador_idx].id, elevadores[elevador_idx].corredor, corredor_destino);
        elevadores[elevador_idx].corredor = corredor_destino;
    }

    printf("Elevador %d: Indo para o Andar %d\n", elevadores[elevador_idx].id, destino_andar);

    while (elevadores[elevador_idx].andar_atual != destino_andar) {
        if (elevadores[elevador_idx].andar_atual < destino_andar) {
            elevadores[elevador_idx].andar_atual++;
        } else {
            elevadores[elevador_idx].andar_atual--;
        }

        exibir_estado_elevadores();
        usleep(500000);  // Pausa de 0,5 segundo para a animação

        // Verificar colisões antes de prosseguir para o próximo andar
        if (verificar_colisao(elevador_idx, elevadores[elevador_idx].andar_atual)) {
            printf("Elevador %d: Colisão detectada. Parando no andar %d\n", elevadores[elevador_idx].id, elevadores[elevador_idx].andar_atual);
            break;
        }
    }

    printf("Elevador %d: Chegou ao Andar %d\n", elevadores[elevador_idx].id, elevadores[elevador_idx].andar_atual);
    elevadores[elevador_idx].em_movimento = 0;
}

void processar_chamada(int andar_chamada, int corredor_chamada) {
    int elevador_idx = encontrar_elevador_disponivel(andar_chamada, corredor_chamada);

    if (elevador_idx != -1) {
        elevadores[elevador_idx].em_movimento = 1;
        printf("Elevador %d: Iniciando movimento\n", elevadores[elevador_idx].id);
        exibir_estado_elevadores();  // Exibir estado inicial do elevador
        mover_elevador(elevador_idx, andar_chamada);
        return;
    }

    printf("Nenhum elevador disponível no Corredor %d. Procurando no próximo corredor...\n", corredor_chamada);

    int corredor_proximo = (corredor_chamada + 1) % NUM_CORREDORES;
    elevador_idx = encontrar_elevador_disponivel(andar_chamada, corredor_proximo);

    if (elevador_idx != -1) {
        elevadores[elevador_idx].em_movimento = 1;
        printf("Elevador %d: Iniciando movimento\n", elevadores[elevador_idx].id);
        exibir_estado_elevadores();  // Exibir estado inicial do elevador
        mover_elevador(elevador_idx, andar_chamada);
        return;
    }

    printf("Nenhum elevador disponível. Aguarde...\n");
}

void gerar_chamadas_aleatorias() {
    srand(time(NULL));

    int i;
    for (i = 0; i < NUM_ANDARES_TOTAL; i++) {
        chamadas[i].andar_chamada = rand() % (NUM_ANDARES_TOTAL - 1) + 1;
        chamadas[i].corredor_chamada = rand() % NUM_CORREDORES;
    }
}

int main() {
    inicializar_elevadores();
    gerar_chamadas_aleatorias();

    int i;
    for (i = 0; i < NUM_ANDARES_TOTAL; i++) {
        exibir_chamada(chamadas[i].andar_chamada, chamadas[i].corredor_chamada);
        processar_chamada(chamadas[i].andar_chamada, chamadas[i].corredor_chamada);
    }

    return 0;
}
