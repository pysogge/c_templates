#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

char *get_timestamped_string() {
    char *timestamped_string;
    time_t current_time;
    struct tm *time_info;
    struct timeval tv;
    int milliseconds;

    timestamped_string = malloc(20);
    if (timestamped_string == NULL) {
        return NULL;
    }

    current_time = time(NULL);
    time_info = gmtime(&current_time);

    gettimeofday(&tv, NULL);
    milliseconds = tv.tv_usec / 1000;

    sprintf(timestamped_string, "%04d%02d%02d.%02d%02d%02d.%03d",
            time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, milliseconds);

    return timestamped_string;
}

int main() {
    char *timestamped_string = get_timestamped_string();
    printf("Timestamped string: %s\n", timestamped_string);
    free(timestamped_string);

    return 0;
}