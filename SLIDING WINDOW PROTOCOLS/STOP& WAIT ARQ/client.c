#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define TIMEOUT_VALUE 5

void main() {
    char *ip = "127.0.0.1";
    int port = 5579;
    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;
    int packetCounter = 0;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-] Socket error ");
        exit(1);
    }

    // Initialize server address
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    while (packetCounter < 7) {
        bzero(buffer, 1024);
        sprintf(buffer, "%d", packetCounter);
        printf("Client: Sending packet %d\n", packetCounter);
        sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));

        // Set socket timeout
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT_VALUE;
        timeout.tv_usec = 0;

        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
            perror("Error setting socket options");
        } else {
            bzero(buffer, 1024);
            addr_size = sizeof(addr);
            int rec = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
            if (rec < 0) {
                printf("Client: Timeout error! Sending packet %d again\n", packetCounter);
            } else {
                printf("Client: Received acknowledgment for packet %d\n", packetCounter);
                packetCounter++;
            }
        }
        sleep(1);
    }

    close(sockfd);
}
