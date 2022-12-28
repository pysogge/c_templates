#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Run the process and get a stream to its output
    FILE* fp = popen("process", "r");

    // Set the file descriptor for the stream to non-blocking mode
    int fd = fileno(fp);
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return 1;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        return 1;
    }

    // Read from the stream using fgets
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("Output: %s", line);
    }

    // Close the stream
    pclose(fp);
    return 0;
}
