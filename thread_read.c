#include <stdio.h>
#include <pthread.h>

void* read_thread(void* arg) {
    // Get the stream from the argument
    FILE* fp = (FILE*)arg;

    // Read from the stream using fgets
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("Output: %s", line);
    }

    return NULL;
}

int main(int argc, char** argv) {
    // Run the process and get a stream to its output
    FILE* fp = popen("process", "r");

    // Create a separate thread to read from the stream
    pthread_t thread;
    pthread_create(&thread, NULL, read_thread, (void*)fp);

    // Do other work here while the stream is being read in the separate thread...

    // Wait for the read thread to finish
    pthread_join(thread, NULL);

    // Close the stream
    pclose(fp);
    return 0;
}
