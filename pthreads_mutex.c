#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_resource = 0;

void *increment_resource(void *arg) {
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        shared_resource++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_resource, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Shared resource: %d\n", shared_resource);  // Shared resource: 400

    return 0;
}

// One way to synchronize access to a shared resource in a C program using pthreads is to use a mutex (mutual exclusion) lock. A mutex lock allows only one thread to access the shared resource at a time, ensuring that the resource is accessed and modified in a thread-safe manner.