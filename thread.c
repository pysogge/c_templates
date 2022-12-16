#include <pthread.h>

void *thread_function(void *arg) {
  // This function will be executed in a separate thread
  // arg is a pointer to any data that was passed to the thread
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t thread;
  int result = pthread_create(&thread, NULL, thread_function, NULL);
  if (result != 0) {
    // Handle the error
  }
  // The main thread will continue to execute here while the new thread executes the thread_function
  pthread_join(thread, NULL); // Wait for the thread to finish
  return 0;
}
