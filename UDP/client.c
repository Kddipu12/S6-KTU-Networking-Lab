#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

void main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 5566; // Server port number
    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[ -] Socket error ");
        exit(1);
    }

    // Clear server address structure
    memset(&addr, '\0', sizeof(addr));

    // Set server address family, port, and IP address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Clear buffer
    bzero(buffer, 1024);

    // Get user input to send to server
    printf("Enter the data: ");
    scanf(" %[^\n]", buffer);
    printf("(Client) Data to server: %s\n", buffer);

    // Send data to server
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));

    // Clear buffer for receiving response
    bzero(buffer, 1024);

    // Initialize the size of the server address structure
    addr_size = sizeof(addr);

    // Receive response from server
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
    printf("(Client) Data from server: %s\n", buffer);
}
