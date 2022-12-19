#ifndef LOGGER_H
#define LOGGER_H

struct Logger {
    int log_level;
    char *log_file_path;
};

struct Logger *create_logger(int log_level, char *log_file_path);
void LOG(struct Logger *logger, int level, char *message) ;
void destroy_logger(struct Logger *logger);

#endif