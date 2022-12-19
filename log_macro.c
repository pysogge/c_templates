#define LOG(level, message) \
  do { \
    if (level <= g_log_level) { \
      printf("[%s] %s\n", #level, message); \
    } \
  } while (0)


int g_log_level = 0;

void set_log_level(int level) {
  g_log_level = level;
}

LOG(0, "This is a debug message");
LOG(1, "This is an info message");
LOG(2, "This is a warning message");
LOG(3, "This is an error message");
