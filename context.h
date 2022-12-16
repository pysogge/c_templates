#ifndef CONTEXT_H
#define CONTEXT_H

#include <pthread.h>

struct context {
  // Configuration data
  char *config_file;
  int log_level;

  // Global variables
  int global_var1;
  char *global_var2;

  // Subprocesses
  pid_t subprocess1;
  pid_t subprocess2;
};

void process_data(struct context *ctx);

#endif