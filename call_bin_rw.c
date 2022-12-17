#include <stdio.h>
#include <unistd.h>

int main() {
  // Open a stream to the process
  FILE *stream = popen("/path/to/process", "w");

  // Redirect the process's standard input and output to the stream
  dup2(fileno(stream), STDIN_FILENO);
  dup2(fileno(stream), STDOUT_FILENO);

  // Write input data to the process
  fputs("input data\n", stream);
  fflush(stream);

  // Read the output of the process
  char output[1024];
  while (fgets(output, sizeof(output), stream) != NULL) {
    printf("%s", output);
  }

  // Close the stream
  pclose(stream);

  return 0;
}
