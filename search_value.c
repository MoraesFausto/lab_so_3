#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *array;
    int start;
    int end;
    int value;
    int found; // Flag para indicar se o valor foi encontrado
} ThreadData;

void *search_value(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] == data->value) {
            data->found = 1; // Marca que o valor foi encontrado
            pthread_exit(NULL); // Sai da thread
        }
    }

    pthread_exit(NULL); // Sai da thread se não encontrar o valor
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <array_size> <value_to_find> <n_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int array_size = atoi(argv[1]);
    int value_to_find = atoi(argv[2]);
    int n_threads = atoi(argv[3]);

    // Aloca e inicializa o vetor aleatorio
    int *array = (int *)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 100;
    }

    pthread_t *threads = (pthread_t *)malloc(n_threads * sizeof(pthread_t));
    ThreadData *thread_data = (ThreadData *)malloc(n_threads * sizeof(ThreadData));

    int segment_size = array_size / n_threads;

    // Cria as threads
    for (int i = 0; i < n_threads; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i == n_threads - 1) ? array_size : (i + 1) * segment_size;
        thread_data[i].value = value_to_find;
        thread_data[i].found = 0;

        pthread_create(&threads[i], NULL, search_value, &thread_data[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Verifica se o valor foi encontrado
    int value_found = 0;
    for (int i = 0; i < n_threads; i++) {
        if (thread_data[i].found) {
            value_found = 1;
            break;
        }
    }

    if (value_found) {
        printf("Value %d found in the array.\n", value_to_find);
    } else {
        printf("Value %d not found in the array.\n", value_to_find);
    }

    // Libera a memória
    free(array);
    free(threads);
    free(thread_data);

    return EXIT_SUCCESS;
}
