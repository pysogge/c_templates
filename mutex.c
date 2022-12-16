#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mutex for synchronizing access to the file
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function for reading the file
void *read_file(void *arg) {
    // Open the file
    FILE *fp = fopen("file.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Lock the mutex to synchronize access to the file
    pthread_mutex_lock(&mutex);

    // Read the file
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Do something with the line
        printf("Read: %s", line);
    }

    // Close the file and unlock the mutex
    fclose(fp);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Function for writing to the file
void *write_file(void *arg) {
    // Open the file
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Lock the mutex to synchronize access to the file
    pthread_mutex_lock(&mutex);

    // Write to the file
    fprintf(fp, "Hello, world!\n");

    // Close the file and unlock the mutex
    fclose(fp);
    pthread_mutex_unlock(&mutex);

    return NULL;
}