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

    // Use the unused fd to open a file
    FILE* file = fdopen(fd, "r");
    if (file == NULL) {
        perror("fdopen");
        return 1;
    }

    // Read from the file
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        if (ferror(file)) {
            perror("fgets");
        }
        return 1;
    }

    return 0;
}
