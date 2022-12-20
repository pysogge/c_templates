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
        // // This is the child process. Close the write end of the pipe.
        // close(pipefd[1]);

        // // Connect the read end of the pipe to the child's standard input.
        // dup2(pipefd[0], STDIN_FILENO);

        // This is the child process. Close the read end of the pipe.
        close(pipefd[0]);

        // Connect the write end of the pipe to the child's standard output.
        dup2(pipefd[1], STDOUT_FILENO);

        // Execute the new program.
        execl("/path/to/program", "program_name", NULL);
    } else if (pid > 0) {
        // // This is the parent process. Close the read end of the pipe.
        // close(pipefd[0]);

        // Connect the write end of the pipe to the parent's standard output.
        // dup2(pipefd[1], STDOUT_FILENO);

        // Connect the read end of the pipe to a new unused fd
        int newfd = 3;
        dup2(pipefd[0], newfd);

        // CLose the write end of the pipe.
        close(pipefd[1]);

        // While there is data, read a line from the pipe and print it to the screen, but after five lines, break
        char buf[1024];
        int i = 0;
        while (read(pipefd[0], buf, sizeof(buf)) > 0) {
            printf("%s", buf);
            if (++i == 5) {
                break;
            }
        }

        // While there is data, read a line from the pipe with fgets and print it to the screen, but after five lines, break
        // char buf[1024];
        // int i = 0;
        // while (fgets(buf, sizeof(buf), pipefd[0]) != NULL) {
        //     printf("%s", buf);
        //     if (++i == 5) {
        //         break;
        //     }
        // }

        // close the read end of the pipe
        close(pipefd[0]);

        // kill the child process
        kill(pid, SIGKILL);

        // Or Wait for the child process to finish.
        int status;
        wait(&status);
    } else {
        // fork failed
        perror("fork");
        return 1;
    }

    return 0;
}
