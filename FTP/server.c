#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 1030
#define BUFFER_SIZE 1024

void main() {
    int server_sock, client_sock;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addr_size;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    } else {
        printf("Successfully created socket\n");
    }

    // Initialize the server address structure with zero
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;             // IPv4
    serveraddr.sin_port = htons(PORT);           // Port number
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP

    // Bind the socket to the IP address and port
    if (bind(server_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Error binding");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_sock, 10);
    printf("Server is listening on port %d\n", PORT);

    // Accept the client connection
    addr_size = sizeof(clientaddr);
    client_sock = accept(server_sock, (struct sockaddr *)&clientaddr, &addr_size);
    if (client_sock < 0) {
        perror("Error accepting connection");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char filename[100];
    FILE *fptr;

    while (1) {
        bzero(buffer, BUFFER_SIZE);  // Clear the buffer
        recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive command from client

        if (strcmp(buffer, "PUT") == 0) {
            // Client wants to upload a file
            bzero(buffer, BUFFER_SIZE);
            recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive filename
            strcpy(filename, buffer);

            bzero(buffer, BUFFER_SIZE);
            fptr = fopen(filename, "w");  // Open file for writing
            if (!fptr) {
                perror("Error opening file");
                continue;
            }

            while (1) {
                bzero(buffer, BUFFER_SIZE);
                recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive file content
                if (strcmp(buffer, "END$") == 0) {
                    break;  // End of file
                }
                fprintf(fptr, "%s", buffer); // Write to file
            }
            printf("File %s received\n", filename);
            fclose(fptr);  // Close the file

        } else if (strcmp(buffer, "GET") == 0) {
            // Client wants to download a file
            bzero(buffer, BUFFER_SIZE);
            sprintf(buffer, "%d", getpid()); // Send server process ID to client
            send(client_sock, buffer, BUFFER_SIZE, 0);

            bzero(buffer, BUFFER_SIZE);
            recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive filename
            strcpy(filename, buffer);

            bzero(buffer, BUFFER_SIZE);
            fptr = fopen(filename, "r");  // Open file for reading
            if (!fptr) {
                // File not found
                printf("The given file does not exist\n");
                strcpy(buffer, "404");
                send(client_sock, buffer, BUFFER_SIZE, 0); // Send 404 error to client
            } else {
                // File found
                strcpy(buffer, "200");
                send(client_sock, buffer, BUFFER_SIZE, 0); // Send 200 OK to client

                while (fgets(buffer, BUFFER_SIZE, fptr)) {
                    // Send file content to client
                    send(client_sock, buffer, BUFFER_SIZE, 0);
                    bzero(buffer, BUFFER_SIZE);
                }
                strcpy(buffer, "END$");
                send(client_sock, buffer, BUFFER_SIZE, 0); // End of file
                fclose(fptr); // Close the file
                printf("File %s sent\n", filename);
            }
        } else if (strcmp(buffer, "BYE") == 0) {
            // Client wants to disconnect
            close(client_sock); // Close the client socket
            close(server_sock); // Close the server socket
            exit(0); // Exit the program
        }
    }
}
