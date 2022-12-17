#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Unable to create socket");
        return 1;
    }

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Unable to bind socket");
        return 1;
    }

    // receive frames
    while (1) {
        char buffer[65535];
        struct sockaddr_in sender_addr;
        socklen_t addr_len = sizeof(sender_addr);

        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &addr_len);

        if (n == -1) {
            perror("Unable to receive data");
            return 1;
        }

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char filename[256];
        snprintf(filename, sizeof(filename), "frame_%04d%02d%02d%02d%02d%02d.bin", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        FILE *fp = fopen(filename, "wb");
        if (fp == NULL) {
            perror("Unable to open file");
            return 1;
        }
    }

    return 0;
}
