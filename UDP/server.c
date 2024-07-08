#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ctype.h>

void main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 5566; // Server port number
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[ -] Socket error ");
        exit(1);
    }

    // Clear server address structure
    memset(&server_addr, '\0', sizeof(server_addr));

    // Set server address family, port, and IP address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind the socket to the server address
    n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("[+] Bind error ");
        exit(1);
    }

    // Clear buffer
    bzero(buffer, 1024);

    // Initialize the size of the client address structure
    addr_size = sizeof(client_addr);

    // Receive data from the client
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
    printf("[+] Data from client: %s\n", buffer);

    // Prepare response to client
    strcpy(buffer, "Data successfully received.");
    printf("(Server) Data to client: %s\n", buffer);

    // Send response back to client
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
}
