#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 12345
#define BACKLOG 10

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) < 0) {
        perror("Error listening on socket");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_sockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    char buffer[1024];

    while (1) {
        int n = recv(client_sockfd, buffer, sizeof(buffer), 0);

        if (n < 0) {
            perror("Error receiving data");
            exit(1);
        }

        if (n == 0) {
            break;
        }

        printf("Received %d bytes: %s ", n, buffer);

        n = send(client_sockfd, buffer, n, 0);

        if (n < 0) {
            perror("Error sending data");
            exit(1);
        }

        printf("Sent %d bytes: %s ", n, buffer);

        memset(buffer, 0, sizeof(buffer));

        sleep(1);
    }

    close(client_sockfd);

    return 0;
}