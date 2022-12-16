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

struct context ctx;

void process_data(struct context *ctx) {
  // Use the state stored in the context struct
  printf("Log level: %d\n", ctx->log_level);
  printf("Global variable 1: %d\n", ctx->global_var1);
  printf("Global variable 2: %s\n", ctx->global_var2);
}