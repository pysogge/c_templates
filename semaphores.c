#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Semaphore for controlling access to the shared resource
sem_t sem;

// Shared resource
int shared_resource = 0;

// Thread function that accesses the shared resource
void *thread_func(void *arg) {
  // Wait on the semaphore
  sem_wait(&sem);

  // Access the shared resource
  shared_resource += 1;
  printf("Thread %ld: shared_resource = %d\n", (long)arg, shared_resource);

  // Release the semaphore
  sem_post(&sem);

  return NULL;
}

int main(int argc, char *argv[]) {
  // Initialize the semaphore with a value of 1
  sem_init(&sem, 0, 1);

  // Create two threads
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, thread_func, (void *)1);
  pthread_create(&thread2, NULL, thread_func, (void *)2);

  // Wait for the threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Destroy the semaphore
  sem_destroy(&sem);

  return 0;
}
