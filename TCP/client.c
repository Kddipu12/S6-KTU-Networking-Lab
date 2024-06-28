#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAX 80
#define SA struct sockaddr
#define PORT 5051

// Function designed for chat between client and server
void chat(int sockfd) {
    char buffer[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buffer, MAX);
        printf("Enter the string : ");
        n = 0;
        while ((buffer[n++] = getchar()) != '\n');
        
        // send the buffer to server
        write(sockfd, buffer, sizeof(buffer));
        
        bzero(buffer, MAX);
        
        // read the message from the server and copy it in buffer
        read(sockfd, buffer, sizeof(buffer));
        
        // print server content
        printf("From server: %s", buffer);
        
        // if msg contains "Exit" then client exit and chat ended
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Client Exit ..\n");
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in serveraddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Socket creation failed..\n");
        exit(0);
    } else 
        printf("Socket creation successful..\n");

    bzero(&serveraddr, sizeof(serveraddr));

    // assign IP, PORT
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost or server IP
    serveraddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
        printf("Connection with server failed\n");
        exit(0);
    } else
        printf("Connected to server successfully\n");

    // Function for chatting between the client and server
    chat(sockfd);

    // Close the socket
    close(sockfd);

    return 0;
}
