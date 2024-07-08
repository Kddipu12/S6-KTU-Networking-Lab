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
    int client_sock;
    struct sockaddr_in serveraddr;

    // Create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    } else {
        printf("Successfully created socket\n");
    }

    // Initialize the server address structure with zero
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;              // IPv4
    serveraddr.sin_port = htons(PORT);            // Port number
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP

    // Connect to the server
    if (connect(client_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Error connecting to server");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char filename[100];
    int choice;
    FILE *fptr;

    while (1) {
        // Present options to the user
        printf("\n1. Upload a file (PUT)\n2. Download a file (GET)\n3. Exit (BYE)\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Upload a file to the server
                bzero(buffer, BUFFER_SIZE);        // Clear the buffer
                strcpy(buffer, "PUT");             // Send "PUT" command to the server
                send(client_sock, buffer, BUFFER_SIZE, 0);

                printf("Enter the filename: ");
                scanf("%s", filename);

                fptr = fopen(filename, "r");       // Open file for reading
                if (!fptr) {
                    printf("The given file does not exist\n");
                } else {
                    bzero(buffer, BUFFER_SIZE);
                    strcpy(buffer, filename);      // Send the filename to the server
                    send(client_sock, buffer, BUFFER_SIZE, 0);

                    // Send file content
                    while (fgets(buffer, BUFFER_SIZE, fptr)) {
                        send(client_sock, buffer, BUFFER_SIZE, 0);
                        bzero(buffer, BUFFER_SIZE);
                    }
                    bzero(buffer, BUFFER_SIZE);
                    strcpy(buffer, "END$");        // Send end of file indicator
                    send(client_sock, buffer, BUFFER_SIZE, 0);
                    fclose(fptr);                  // Close the file
                    printf("File %s sent\n", filename);
                }
                break;

            case 2:
                // Download a file from the server
                bzero(buffer, BUFFER_SIZE);        // Clear the buffer
                strcpy(buffer, "GET");             // Send "GET" command to the server
                send(client_sock, buffer, BUFFER_SIZE, 0);

                bzero(buffer, BUFFER_SIZE);
                recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive server process ID
                printf("Process ID: %s\n", buffer);

                printf("Enter the filename: ");
                scanf("%s", filename);

                bzero(buffer, BUFFER_SIZE);
                strcpy(buffer, filename);          // Send the filename to the server
                send(client_sock, buffer, BUFFER_SIZE, 0);

                bzero(buffer, BUFFER_SIZE);
                recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive response code

                if (strcmp(buffer, "404") == 0) {
                    // File not found on the server
                    printf("File does not exist on the remote server\n");
                } else if (strcmp(buffer, "200") == 0) {
                    // File found, start receiving content
                    fptr = fopen(filename, "w");   // Open file for writing
                    if (!fptr) {
                        perror("Error opening file");
                        break;
                    }
                    while (1) {
                        bzero(buffer, BUFFER_SIZE);
                        recv(client_sock, buffer, BUFFER_SIZE, 0); // Receive file content
                        if (strcmp(buffer, "END$") == 0)
                            break;                 // End of file
                        fprintf(fptr, "%s", buffer); // Write to file
                        printf("%s", buffer);
                    }
                    fclose(fptr);                  // Close the file
                    printf("File %s received\n", filename);
                }
                break;

            case 3:
                // Exit the program
                bzero(buffer, BUFFER_SIZE);        // Clear the buffer
                strcpy(buffer, "BYE");             // Send "BYE" command to the server
                send(client_sock, buffer, BUFFER_SIZE, 0);
                close(client_sock);                // Close the socket
                printf("Disconnected from server\n");
                exit(EXIT_SUCCESS);                // Exit the program

            default:
                printf("Invalid choice, please try again\n");
        }
    }
}
