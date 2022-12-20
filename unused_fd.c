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

    return 0;
}
