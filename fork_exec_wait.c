#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Create a new process
    pid_t pid = fork();

    if (pid == 0) {
        // This is the child process. Execute the new program.
        execl("/path/to/program", "program_name", "arg1", "arg2", NULL);
    } else if (pid > 0) {
        // This is the parent process. Wait for the child process to finish.
        int status;
        wait(&status);
    } else {
        // fork failed
        perror("fork");
        return 1;
    }

    return 0;
}
