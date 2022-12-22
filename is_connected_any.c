#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Run the ping command
  int result = system("ping -c 1 google.com > /dev/null");

  // Check the result
  if (result == 0) {
    // The ping was successful
    printf("Internet connection is available\n");
    return 0;
  } else {
    // The ping failed
    printf("Internet connection is not available\n");
    return 1;
  }
}
