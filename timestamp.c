#include <stdio.h>
#include <time.h>

#define TIMESTAMP_SIZE 20

char *get_timestamp_str(void) {
  time_t rawtime;
  struct tm *timeinfo;
  static char timestamp_str[TIMESTAMP_SIZE];

  // Get the current time
  time(&rawtime);

  // Convert the time to a local time structure
  timeinfo = localtime(&rawtime);

  // Format the time as a string
  strftime(timestamp_str, TIMESTAMP_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

  // Return the formatted string
  return timestamp_str;
}

int main(void) {
  // Get the timestamp string
  char *timestamp_str = get_timestamp_str();

  // Print the resulting string
  printf("Timestamp: %s\n", timestamp_str);

  return 0;
}
