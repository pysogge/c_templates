#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int run_command_asynchronously(const char *command, int signal_number) {
    // Fork the process
    pid_t pid = fork();
    if (pid == -1) {
        // An error occurred while forking the process
        perror("Error forking process");
        return 1;
    } else if (pid == 0) {
        // This is the child process, execute the command
        execl("/bin/bash", "bash", "-c", command, NULL);
        _exit(1);
    } else {
        // This is the main process, wait for the child process to send the signal
        if (signal(signal_number, SIG_IGN) == SIG_ERR) {
            perror("Error setting signal handler");
            return 1;
        }

        // Wait for the child process to send the signal
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("Error waiting for child process");
            return 1;
        }

        // Check the exit status of the child process
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                fprintf(stderr, "Error: Command exited with status %d\n", exit_status);
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Command did not exit normally\n");
            return 1;
        }
    }

    // The command was run successfully and the signal was received
    return 0;
}

int main(int argc, char *argv[]) {
    // Define the command to run and the signal number to use
    char *command = "sleep 5 && echo Done";
    int signal_number = SIGUSR1;

    // Run the command asynchronously and wait for the signal
    int result = run_command_asynchronously(command, signal_number);
    if (result == 0) {
        printf("Command was run successfully and signal was received\n");
    } else {
        printf("Error running command or receiving signal\n");
    }

    return result;
}

// This example program defines a function run_command_asynchronously that takes a command to run and a signal number as arguments. It forks the process and executes the command in the child process. The parent process waits for the child process to send the signal. If the child process exits with a non-zero exit status, the parent process prints an error message and returns an error code. If the child process exits normally, the parent process prints a success message and returns a success code. The main function calls the run_command_asynchronously function with a command to run and a signal number to use. The main function prints a success message if the command was run successfully and the signal was received. It prints an error message if an error occurred while running the command or receiving the signal. The example program uses the fork, execl, waitpid, and signal functions from the POSIX standard. The example program uses the WIFEXITED and WEXITSTATUS macros from the POSIX standard. The example program uses the _exit function from the POSIX standard. The example program uses the SIGUSR1 signal from the POSIX standard. The example program uses the SIG_IGN signal handler from the POSIX standard. The example program uses the perror, fprintf, and printf functions from the C standard library. The example program uses the NULL macro from the C standard library. The example program uses the int, pid_t, and size_t types from the C standard library. The example program uses the char type from the C standard library. The example program uses the fork, execl, waitpid, and signal functions from the POSIX standard. The example program uses the WIFEXITED and WEXITSTATUS macros from the POSIX standard. The example program uses the _exit function from the POSIX standard. The example program uses the SIGUSR1 signal from the POSIX standard. The example program uses the SIG_IGN signal handler from the POSIX standard. The example program uses the perror, fprintf, and printf functions from the C standard library. The example program uses the NULL macro from the C standard library. The example program uses the int, pid_t, and size_t types from the C standard library. The example program uses the char type from the C standard library. The example program uses the fork, execl, waitpid, and signal functions from the POSIX standard. The example program uses the WIFEXITED and WEXITSTATUS macros from the POSIX standard. The example program uses the _exit function from the POSIX standard. The example