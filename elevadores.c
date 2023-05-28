#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_FLOORS 300
#define NUM_CORRIDORS 3
#define NUM_ELEVATORS 5
#define HORIZONTAL_MOVE_FLOOR 10

typedef struct {
    int floor;
    int corridor;
} Elevator;

Elevator elevators[NUM_CORRIDORS][NUM_ELEVATORS];

bool is_valid_floor(int floor) {
    return floor >= 0 && floor < NUM_FLOORS;
}

bool is_valid_corridor(int corridor) {
    return corridor >= 0 && corridor < NUM_CORRIDORS;
}

void initialize_elevators() {
    srand(time(NULL));
    for (int i = 0; i < NUM_CORRIDORS; i++) {
        for (int j = 0; j < NUM_ELEVATORS; j++) {
            elevators[i][j].floor = rand() % NUM_FLOORS;
            elevators[i][j].corridor = rand() % NUM_CORRIDORS;
        }
    }
}

bool is_elevator_at_floor(int floor, int corridor) {
    for (int j = 0; j < NUM_ELEVATORS; j++) {
        if (elevators[corridor][j].floor == floor) {
            return true;
        }
    }
    return false;
}

int calculate_total_distance(Elevator *elevator, int current_floor, int target_floor, int target_corridor) {
    int vertical_distance = abs(elevator->floor - current_floor) + abs(target_floor - current_floor);
    int horizontal_distance = 0;

    if (elevator->corridor != target_corridor) {
        horizontal_distance = abs((elevator->floor % HORIZONTAL_MOVE_FLOOR) - (target_floor % HORIZONTAL_MOVE_FLOOR)) * HORIZONTAL_MOVE_FLOOR;
    }

    return vertical_distance + horizontal_distance;
}

Elevator *find_closest_elevator(int current_floor, int target_floor, int target_corridor) {
    Elevator *closest_elevator = NULL;
    int min_distance = NUM_FLOORS * (HORIZONTAL_MOVE_FLOOR + 1);

    for (int i = 0; i < NUM_CORRIDORS; i++) {
        for (int j = 0; j < NUM_ELEVATORS; j++) {
            int distance = calculate_total_distance(&elevators[i][j], current_floor, target_floor, target_corridor);
            if (distance < min_distance) {
                min_distance = distance;
                closest_elevator = &elevators[i][j];
            }
        }
    }

    return closest_elevator;
}

int main() {
    initialize_elevators();

    int current_floor, target_floor, target_corridor;

    printf("Posição dos elevadores:\n");
    for (int i = 0; i < NUM_CORRIDORS; i++) {
        for (int j = 0; j < NUM_ELEVATORS; j++) {
            printf("Elevador %d-%d: corredor %d, andar %d\n", i, j, elevators[i][j].corridor, elevators[i][j].floor);
        }
    }


    printf("Digite o andar atual, o andar de destino (0 a 299) e o corredor de destino (0 a 2): ");
    scanf("%d %d %d", &current_floor, &target_floor, &target_corridor);

    if (!is_valid_floor(current_floor) || !is_valid_floor(target_floor) || !is_valid_corridor(target_corridor)) {
        printf("Entrada inválida. Por favor, insira andares entre 0 e 299 e corredores entre 0 e 2.\n");
        return 1;
    }

    Elevator *elevator = find_closest_elevator(current_floor, target_floor, target_corridor);
    Elevator *closest_elevator = elevator;

    printf("\033[32mElevador mais próximo está no corredor %d e no andar %d.\033[0m\n", elevator->corridor, elevator->floor);

    // Verifica se há outro elevador no mesmo corredor e no mesmo andar de destino
    if (is_elevator_at_floor(target_floor, target_corridor)) {
        printf("Há outro elevador no mesmo corredor e no mesmo andar de destino. Procurando outro elevador...\n");
        int min_distance = NUM_FLOORS * (HORIZONTAL_MOVE_FLOOR + 1);
        for (int i = 0; i < NUM_CORRIDORS; i++) {
            for (int j = 0; j < NUM_ELEVATORS; j++) {
                if (elevators[i][j].corridor != target_corridor) {
                    int distance = calculate_total_distance(&elevators[i][j], current_floor, target_floor, target_corridor);
                    if (distance < min_distance) {
                        min_distance = distance;
                        closest_elevator = &elevators[i][j];
                    }
                }
            }
        }
        printf("\033[32mElevador mais próximo que não está no mesmo corredor está no corredor %d e no andar %d.\033[0m\n", closest_elevator->corridor, closest_elevator->floor);
        elevator = closest_elevator;
    }

    elevator->floor = target_floor;
    elevator->corridor = target_corridor;
    printf("Elevador chegou ao andar de destino: %d e corredor de destino: %d.\n", elevator->floor, elevator->corridor);

    0;
}