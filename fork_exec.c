#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Create a new process
    pid_t pid = fork();

    if (pid == 0) {
        // This is the child process. Execute the binary.
        execl("/path/to/binary", "binary_name", NULL);
    } else if (pid > 0) {
        // This is the parent process. Print the pid of the child process.
        printf("Child process pid: %d\n", pid);
    } else {
        // fork failed
        perror("fork");
        return 1;
    }

    return 0;
}

// This code creates a new process with fork, and in the child process it executes the binary binary_name with execl. In the parent process, it prints the pid of the child process.

// Note that the fork and exec functions are part of the POSIX standard and should be available on most systems. However, they have some limitations and may not be suitable for all use cases. For example, exec does not return if the execution of the binary is successful, and it does not provide a way to read or write to the binary's standard input or output. In these cases, you may need to use other functions such as pipe, dup2, and spawn.