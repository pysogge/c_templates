#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int check_connectivity(const char *device) {
  // Build the command to run ping
  char command[256];
  snprintf(command, sizeof(command), "ping -I %s -c 1 google.com > /dev/null", device);

  // Run the command and check the result
  int result = system(command);
  if (result == 0) {
    // The ping was successful
    return 1;
  } else {
    // The ping failed
    return 0;
  }
}

int main(int argc, char *argv[]) {
  // Check the number of arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s device\n", argv[0]);
    return 1;
  }

  // Check the connectivity of the device
  int connectivity = check_connectivity(argv[1]);
  if (connectivity) {
    printf("The device is connected to the internet\n");
  } else {
    printf("The device is not connected to the internet\n");
  }

  return 0;
}
