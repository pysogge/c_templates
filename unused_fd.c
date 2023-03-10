#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    // Find an unused fd
    int fd;
    for (fd = 3; fd < 1024; ++fd) {
        int flags = fcntl(fd, F_GETFD);
        if (flags == -1) {
            // fd is unused
            break;
        }
    }

    if (fd == 1024) {
        // No unused fds were found
        fprintf(stderr, "Error: no unused fds found\n");
        return 1;
    }

    // Use the unused fd
    // ...
    // Open a new stdin pipe and connect it to the unused fd
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Close the read end of the pipe
    close(pipefd[0]);

    // Connect the write end of the pipe to the unused fd
    dup2(pipefd[1], fd);
    

    return 0;
}
