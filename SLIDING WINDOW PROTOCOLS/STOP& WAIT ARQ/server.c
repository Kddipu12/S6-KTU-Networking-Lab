#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
    char *ip = "127.0.0.1";
    int port = 5579;
    srand(time(0));
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int expectedSeqNum = 0;
    int recvSeqNum;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-] Socket error ");
        exit(1);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[+] Bind error ");
        exit(1);
    }

    while (1) {
        // Receive message from client
        bzero(buffer, 1024);
        addr_size = sizeof(client_addr);
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);

        // Extract sequence number from received message
        recvSeqNum = atoi(buffer);

        if (recvSeqNum == expectedSeqNum) {
            printf("Server: Received packet %d\n", recvSeqNum);

            // Randomly decide to send acknowledgment
            if (rand() % 2 == 0) {
                printf("Server: Sending acknowledgment for packet %d\n", recvSeqNum);
                sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
                expectedSeqNum++;  // Increment expected sequence number
            }
        } else {
            printf("Server: Received duplicate packet %d\n", recvSeqNum);
        }
    }
}
