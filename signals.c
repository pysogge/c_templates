#include <signal.h>

void signal_handler(int signal) {
  switch (signal) {
    case SIGINT:
      // Handle Ctrl+C interrupt signal
      break;
    case SIGTERM:
      // Handle termination request signal
      break;
    case SIGHUP:
      // Handle terminal hangup signal
      break;
    default:
      // Handle other signals
      break;
  }
}

int main() {
  // Set signal handler function for SIGINT
  signal(SIGINT, signal_handler);

  // Set signal handler function for SIGTERM
  signal(SIGTERM, signal_handler);

  // Set signal handler function for SIGHUP
  signal(SIGHUP, signal_handler);

  // Rest of program goes here
  return 0;
}

// In the signal handler function, you can include code to perform any actions you want in response to the signal, such as closing files or exiting the program.

// It's important to note that the signal handler function should be designed to execute quickly, as it will be interrupted by the signal and may not have access to certain resources. For example, it's generally not a good idea to call printf or other I/O functions from within a signal handler, as they may not be safe to use.

// If you want to block certain signals while your program is running, you can use the sigprocmask function to modify the signal mask. This allows you to temporarily disable the delivery of certain signals to your program, so that they can be handled at a later time.