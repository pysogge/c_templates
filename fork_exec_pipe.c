#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Create a pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Create a new process
    pid_t pid = fork();

    if (pid == 0) {
        // This is the child process. Close the write end of the pipe.
        close(pipefd[1]);

        // Connect the read end of the pipe to the child's standard input.
        dup2(pipefd[0], STDIN_FILENO);

        // Execute the new program.
        execl("/path/to/program", "program_name", NULL);
    } else if (pid > 0) {
        // This is the parent process. Close the read end of the pipe.
        close(pipefd[0]);

        // Connect the write end of the pipe to the parent's standard output.
        dup2(pipefd[1], STDOUT_FILENO);

        // Wait for the child process to finish.
        int status;
        wait(&status);
    } else {
        // fork failed
        perror("fork");
        return 1;
    }

    return 0;
}
