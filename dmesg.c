#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <regex.h>

// Regex for matching the desired output
regex_t regex;

// Thread function that reads the output of dmesg and searches for the regex match
void *read_output(void *arg) {
  // Open a pipe to dmesg
  FILE *fp = popen("dmesg", "r");
  if (fp == NULL) {
    perror("Error opening pipe");
    return NULL;
  }

  // Read the output of dmesg
  char line[1024];
  while (fgets(line, sizeof(line), fp) != NULL) {
    // Check if the line matches the regex
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      // Do something with the matching line
      printf("Match found: %s", line);
        break;
    }
    }
    // Close the pipe
    pclose(fp);
    return NULL;
}

// Thread function that writes to the dmesg buffer
void *write_output(void *arg) {
  // Open a pipe to dmesg
  FILE *fp = popen("dmesg -c", "w");
  if (fp == NULL) {
    perror("Error opening pipe");
    return NULL;
  }

  // Write to the dmesg buffer
  fprintf(fp, "Hello, world!\n");

  // Close the pipe
  pclose(fp);
  return NULL;
}

int main(int argc, char *argv[]) {
  // Compile the regex pattern
  int status = regcomp(&regex, "Hello, world!", REG_EXTENDED);
  if (status != 0) {
    char error_message[1024];
    regerror(status, &regex, error_message, sizeof(error_message));
    printf("Error compiling regex: %s\n", error_message);
    return 1;
  }

  // Create the threads
  pthread_t read_thread, write_thread;
  pthread_create(&read_thread, NULL, read_output, NULL);
  pthread_create(&write_thread, NULL, write_output, NULL);

  // Wait for the threads to finish
  pthread_join(read_thread, NULL);
  pthread_join(write_thread, NULL);

  // Clean up
  regfree(&regex);
  return 0;
}

// This code compiles the regex pattern, creates two threads, one to read the output of dmesg and the other to write to the dmesg buffer, and then waits for the threads to finish. The read thread uses the regexec() function to check if each line matches the pattern. If a match is found, the code prints the line and breaks out of the loop.

