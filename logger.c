#include "logger.h"

struct Logger *create_logger(int log_level, char *log_file_path) {
    struct Logger *logger = malloc(sizeof(struct Logger));
    logger->log_level = log_level;
    logger->log_file_path = log_file_path;

    // ensure the log dir exists before creating the log file
    if (log_file_path != NULL) {
        char *log_dir = dirname(log_file_path);
        mkdir(log_dir, 0777);
        free(log_dir);

        // create the log file, log timestamp
        FILE *log_file = fopen(log_file_path, "w");
        if (log_file != NULL) {
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char timestamp[64];
            strftime(timestamp, sizeof(timestamp), "%c", tm);
            fprintf(log_file, "Log started at %s\n", timestamp);
            fclose(log_file);
        }
    }

    return logger;
}

void LOG(struct Logger *logger, int level, char *message) {
    // Print to console if log level is less than or equal to the logger's log level
    if (level <= logger->log_level) {
        printf("[%s] %s\n", #level, message);
    }

    // Append to log file regardless of log level, if log file path is not NULL, include timestamp
    if (logger->log_file_path != NULL) {
        FILE *log_file = fopen(logger->log_file_path, "a");
        if (log_file != NULL) {
            fprintf(log_file, "[%s] %s\n", #level, message);
            fclose(log_file);
        }
    }
}

void destroy_logger(struct Logger *logger) {
    free(logger);
}