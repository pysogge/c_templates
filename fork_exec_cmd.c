#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // Child process
        execl("/path/to/convert.ex", "convert.ex", "img.jpg", "img.png", NULL);
        // If execl returns, there was an error
        fprintf(stderr, "Error calling execl!\n");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        pid_t wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            exit(1);
        }
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally\n");
        }
    } else {
        // Error
        perror("fork");
        exit(1);
    }

    return 0;
}

// This program creates a new process using the fork function, which creates a copy of the current process. The child process then calls the execl function, which replaces the child process's code with the code of the specified program, in this case "/path/to/convert.ex". The child process then runs the program with the specified arguments ("convert.ex", "img.jpg", "img.png").

// The parent process waits for the child process to exit using the waitpid function, which returns the exit status of the child process. The WIFEXITED and WEXITSTATUS macros are used to determine whether the child process exited normally and to get the exit status code.

// This way, you can call an external program asynchronously and know when it exits, without blocking the parent process.