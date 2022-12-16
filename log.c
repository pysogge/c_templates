#include <stdio.h>

// Global logging level
#define LOG_LEVEL 2

void log_message(int level, const char *message) {
  if (level <= LOG_LEVEL) {
    printf("%s\n", message);
  }
}

void do_something() {
  log_message(3, "Doing something...");
  // Perform some action
  log_message(3, "Done doing something.");
}

int main(int argc, char *argv[]) {
  do_something();
  return 0;
}

// In this example, the LOG_LEVEL macro is defined as 2, which means that only log messages with a level of 2 or lower will be printed. The log_message function takes a level argument that specifies the log level of the message being logged, and compares it to the LOG_LEVEL macro. If the level argument is less than or equal to LOG_LEVEL, the message is printed to the console using the printf function.

// You can use this approach in the same way to control the logging output produced by functions in different files by including the logging header file in those files and using the log_message function to log messages.