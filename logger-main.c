// Implement Logger
#include <stdio.h>

#include "logger.h"

int main(int argc, char *argv[]) {
    struct Logger *logger = create_logger(1, "log.txt");
    LOG(logger, 0, "This is a debug message");
    LOG(logger, 1, "This is an info message");
    LOG(logger, 2, "This is a warning message");
    LOG(logger, 3, "This is an error message");
    destroy_logger(logger);
    return 0;
}

// Log started at Mon Dec 19 11:36:05 2022
// [0] This is a debug message
// [1] This is an info message
// [2] This is a warning message
// [3] This is an error message
