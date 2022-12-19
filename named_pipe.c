#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "my_fifo"

int main() {
    int pipe_fd;
    char buffer[1024];

    // Create the FIFO if it does not exist
    umask(0);
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    // Open the FIFO for reading and writing
    pipe_fd = open(FIFO_NAME, O_RDWR);

    // Read from the FIFO
    read(pipe_fd, buffer, 1024);
    printf("Received: %s\n", buffer);

    // Write to the FIFO
    strcpy(buffer, "Hello from the other side!");
    write(pipe_fd, buffer, strlen(buffer) + 1);

    // Close the FIFO
    close(pipe_fd);

    return 0;
}
