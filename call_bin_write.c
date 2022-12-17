#include <stdio.h>
#include <unistd.h>

int main() {
  // Open a stream to the binary
  FILE *stream = popen("/path/to/binary", "w");

  // Redirect the binary's standard input to the stream
  dup2(fileno(stream), STDIN_FILENO);

  // Periodically write input data to the binary
  char input[] = "input data\n";
  while (1) {
    fputs(input, stream);
    fflush(stream);
    sleep(1);
  }

  // Close the stream
  pclose(stream);

  return 0;
}
