#include <unistd.h>

int main(int argc, char** argv) {
  pid_t pid = fork();
  if (pid == 0) {
    // This code is executed in the child process
    char *const argv[] = {"subroutine", NULL};
    execv("subroutine", argv);
  } else {
    // This code is executed in the parent process
  }
  return 0;
}
