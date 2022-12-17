#include <stdio.h>
#include <unistd.h>

int main() {
  // Get the pid of the process
  int pid = 12345;

  // Open a stream to the process
  char command[1024];
  sprintf(command, "ps -p %d -o pid,comm", pid);
  FILE *stream = popen(command, "r");

  // Redirect the process's standard output to the stream
  dup2(fileno(stream), STDOUT_FILENO);

  // Read the output of the process
  char output[1024];
  while (fgets(output, sizeof(output), stream) != NULL) {
    printf("%s", output);
  }

  // Close the stream
  pclose(stream);

  return 0;
}
