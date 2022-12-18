#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

struct ThreadData {
    int *array;
    int size;
    int sum;
};

void *calculate_sum(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int *array = data->array;
    int size = data->size;
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    data->sum = sum;

    return NULL;
}

int main(int argc, char **argv) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int array_size = sizeof(array) / sizeof(int);

    // Divide the array into chunks for each thread
    int chunk_size = array_size / NUM_THREADS;
    struct ThreadData data[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].array = &array[i * chunk_size];
        data[i].size = chunk_size;
    }

    // Create the threads
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculate_sum, &data[i]);
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Add up the results
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += data[i].sum;
    }

    printf("Total sum: %d\n", total_sum);  // Total sum: 36

    return 0;
}
