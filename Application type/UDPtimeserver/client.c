#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_PORT 3009
#define MAX_BUFFER_SIZE 1024

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    char buffer[MAX_BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(UDP_PORT);
    
    if (inet_aton("127.0.0.1", &servaddr.sin_addr) == 0) {
        perror("Invalid server address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "time");
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Error sending data");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        printf("Time request sent to the server\n");
    }

    n = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL);
    if (n < 0) {
        perror("Error receiving data");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        buffer[n] = '\0';  // Null-terminate the received string
        printf("Received system time from the server\n");
        printf("System time: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
