#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_FLOORS 300
#define NUM_CORRIDORS 3
#define NUM_ELEVATORS 5
#define HORIZONTAL_MOVE_FLOOR 10
#define SLEEP_TIME 1

typedef struct
{
    int floor;
    int corridor;
    bool moving;
    int call_queue[NUM_FLOORS][NUM_CORRIDORS]; // fila de chamadas
    int queue_size;
    bool corridor_lock[NUM_CORRIDORS]; // bloqueio de corredor
} Elevator;

typedef struct
{
    int current_floor;
    int target_floor;
    int target_corridor;
} Call;

Elevator elevators[NUM_CORRIDORS][NUM_ELEVATORS];

bool is_valid_floor(int floor)
{
    return floor >= 0 && floor < NUM_FLOORS;
}

bool is_valid_corridor(int corridor)
{
    return corridor >= 0 && corridor < NUM_CORRIDORS;
}

void initialize_elevators()
{
    srand(time(NULL));
    for (int i = 0; i < NUM_CORRIDORS; i++)
    {
        for (int j = 0; j < NUM_ELEVATORS; j++)
        {
            elevators[i][j].floor = rand() % NUM_FLOORS;
            elevators[i][j].corridor = rand() % NUM_CORRIDORS;
            elevators[i][j].moving = false;
            elevators[i][j].queue_size = 0;
            for (int k = 0; k < NUM_CORRIDORS; k++)
            {
                elevators[i][j].corridor_lock[k] = false;
            }
        }
    }
}

void print_moving_elevators()
{
    printf("Elevadores em movimento:\n");
    for (int i = 0; i < NUM_CORRIDORS; i++)
    {
        for (int j = 0; j < NUM_ELEVATORS; j++)
        {
            if (elevators[i][j].moving)
            {
                printf("Elevador %d-%d: corredor %d, andar %d\n", i, j, elevators[i][j].corridor, elevators[i][j].floor);
            }
        }
    }
}

bool is_elevator_at_floor(int floor, int corridor)
{
    for (int j = 0; j < NUM_ELEVATORS; j++)
    {
        if (elevators[corridor][j].floor == floor)
        {
            return true;
        }
    }
    return false;
}

int calculate_total_distance(Elevator *elevator, int current_floor, int target_floor, int target_corridor)
{
    int vertical_distance = abs(elevator->floor - current_floor) + abs(target_floor - current_floor);
    int horizontal_distance = 0;

    if (elevator->corridor != target_corridor)
    {
        horizontal_distance = abs((elevator->floor % HORIZONTAL_MOVE_FLOOR) - (target_floor % HORIZONTAL_MOVE_FLOOR)) * HORIZONTAL_MOVE_FLOOR;
    }

    return vertical_distance + horizontal_distance;
}

Elevator *find_closest_elevator(int current_floor, int target_floor, int target_corridor)
{
    Elevator *closest_elevator = NULL;
    int min_distance = NUM_FLOORS * (HORIZONTAL_MOVE_FLOOR + 1);

    for (int i = 0; i < NUM_CORRIDORS; i++)
    {
        for (int j = 0; j < NUM_ELEVATORS; j++)
        {
            // Verifica se o elevador está em movimento
            if (elevators[i][j].moving)
            {
                continue;
            }

            // Verifica se o elevador está na mesma rota
            if (elevators[i][j].floor % HORIZONTAL_MOVE_FLOOR != target_floor % HORIZONTAL_MOVE_FLOOR)
            {
                continue;
            }

            int distance = calculate_total_distance(&elevators[i][j], current_floor, target_floor, target_corridor);
            if (distance < min_distance)
            {
                min_distance = distance;
                closest_elevator = &elevators[i][j];
            }
        }
    }

    return closest_elevator;
}

void *handle_call(void *arg)
{
    Call *call = (Call *)arg;
    int current_floor = call->current_floor;
    int target_floor = call->target_floor;
    int target_corridor = call->target_corridor;
    free(call);

    Elevator *elevator = find_closest_elevator(current_floor, target_floor, target_corridor);

    if (elevator == NULL)
    {
        sleep(SLEEP_TIME);
        handle_call(arg);
        return NULL;
    }

    printf("\033[32mElevador mais próximo está no corredor %d e no andar %d.\033[0m\n", elevator->corridor, elevator->floor);

    // Adiciona a chamada à fila do elevador correspondente
    elevator->call_queue[elevator->queue_size][0] = target_floor;
    elevator->call_queue[elevator->queue_size][1] = target_corridor;
    elevator->queue_size++;

    // Se o elevador não estiver em movimento, designa-o para atender a chamada
    if (!elevator->moving)
    {
        bool reused_elevator = false;

        // Verifica se há algum elevador na mesma rota que já está em movimento
        for (int i = 0; i < NUM_ELEVATORS; i++)
        {
            if (elevators[elevator->corridor][i].moving && elevators[elevator->corridor][i].floor % HORIZONTAL_MOVE_FLOOR == target_floor % HORIZONTAL_MOVE_FLOOR)
            {
                reused_elevator = true;
                printf("\033[33mElevador reaproveitado no corredor %d e no andar %d.\033[0m\n", elevator->corridor, elevator->floor);
                break;
            }
        }

        elevator->moving = true;

        for (int i = 0; i < elevator->queue_size; i++)
        {
            int target_floor = elevator->call_queue[i][0];
            int target_corridor = elevator->call_queue[i][1];

            // Simula o tempo que leva para o elevador chegar ao andar de destino
            sleep(SLEEP_TIME);

            // Desbloqueia o corredor anterior
            if (i > 0)
            {
                elevator->corridor_lock[elevator->call_queue[i - 1][1]] = false;
            }

            // Bloqueia o corredor atual
            elevator->corridor_lock[target_corridor] = true;

            elevator->floor = target_floor;
            elevator->corridor = target_corridor;
            printf("Elevador chegou ao andar de destino: %d e corredor de destino: %d.\n", elevator->floor, elevator->corridor);
        }

        // Desbloqueia o corredor final
        elevator->corridor_lock[elevator->call_queue[elevator->queue_size - 1][1]] = false;

        elevator->queue_size = 0;
        elevator->moving = false;

        // Se o elevador foi reaproveitado, não é necessário esperar pela chamada seguinte
        if (reused_elevator)
        {
            return NULL;
        }
    }

    return NULL;
}

int main()
{
    initialize_elevators();

    printf("Posição dos elevadores:\n");
    for (int i = 0; i < NUM_CORRIDORS; i++)
    {
        for (int j = 0; j < NUM_ELEVATORS; j++)
        {
            printf("Elevador %d-%d: corredor %d, andar %d\n", i, j, elevators[i][j].corridor, elevators[i][j].floor);
        }
    }

    int input_count = 0;
    int inputs[100][3];

    while (1)
    {
        printf("Digite o andar atual, o andar de destino (0 a 299) e o corredor de destino (0 a 2) ou -1 para encerrar: ");
        int current_floor;
        scanf("%d", &current_floor);

        if (current_floor == -1)
        {
            break;
        }

        int target_floor, target_corridor;
        scanf("%d %d", &target_floor, &target_corridor);

        if (!is_valid_floor(current_floor) || !is_valid_floor(target_floor) || !is_valid_corridor(target_corridor))
        {
            printf("Entrada inválida. Por favor, insira andares entre 0 e 299 e corredores entre 0 e 2.\n");
            continue;
        }

        inputs[input_count][0] = current_floor;
        inputs[input_count][1] = target_floor;
        inputs[input_count][2] = target_corridor;
        input_count++;
    }

    pthread_t call_threads[input_count];

    for (int i = 0; i < input_count; i++)
    {
        Call *call = (Call *)malloc(sizeof(Call));
        call->current_floor = inputs[i][0];
        call->target_floor = inputs[i][1];
        call->target_corridor = inputs[i][2];

        // Verifica se o corredor está bloqueado por outro elevador em movimento
        bool corridor_blocked = false;
        for (int j = 0; j < NUM_ELEVATORS; j++)
        {
            if (elevators[call->target_corridor][j].moving && elevators[call->target_corridor][j].corridor_lock[call->target_corridor])
            {
                corridor_blocked = true;
                break;
            }
        }

        if (corridor_blocked)
        {
            printf("O corredor está bloqueado por outro elevador em movimento. Por favor, aguarde um momento e tente novamente.\n");
            sleep(SLEEP_TIME);
            continue;
        }

        pthread_create(&call_threads[i], NULL, handle_call, (void *)call);
    }

    for (int i = 0; i < input_count; i++)
    {
        pthread_join(call_threads[i], NULL);
    }

    return 0;
}
