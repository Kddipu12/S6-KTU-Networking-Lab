#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

#define UDP_PORT 3009
#define MAX_BUFFER_SIZE 1024

int main() {
    int sockfd, n;
    char buff[MAX_BUFFER_SIZE];
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t cli_len = sizeof(clientaddr);
    pid_t pid;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(UDP_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        n = recvfrom(sockfd, buff, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&clientaddr, &cli_len);
        if (n < 0) {
            perror("Error receiving data");
            close(sockfd);
            exit(EXIT_FAILURE);
        } else {
            buff[n] = '\0';  // Null-terminate the received string
            printf("Received request from client: %s\n", buff);
        }

        if ((pid = fork()) < 0) {
            perror("Error forking process");
            close(sockfd);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (strcmp(buff, "time") == 0) {
                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                char current_time[MAX_BUFFER_SIZE];
                strftime(current_time, MAX_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", tm);
                if (sendto(sockfd, current_time, strlen(current_time), 0, (struct sockaddr *)&clientaddr, cli_len) < 0) {
                    perror("Error sending data");
                    close(sockfd);
                    exit(EXIT_FAILURE);
                } else {
                    printf("Sent current system time to the client\n");
                }
            }
            close(sockfd);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            // Do not close cli_len, just wait for the next request
        }
    }

    close(sockfd);
    return 0;
}
