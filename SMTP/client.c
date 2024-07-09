#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8088
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE];
    int option;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    while (1) {
        // Display menu
        printf("\nSMTP Client Commands:\n");
        printf("1. HELO\n");
        printf("2. MAIL FROM\n");
        printf("3. RCPT TO\n");
        printf("4. DATA\n");
        printf("5. QUIT\n");
        printf("Select a command: ");
        scanf("%d", &option);
        getchar(); // Consume the newline character left in the input buffer

        switch (option) {
            case 1:
                strcpy(command, "HELO");
                break;
            case 2:
                printf("Enter MAIL FROM content: ");
                fgets(command, BUFFER_SIZE, stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline character
                break;
            case 3:
                printf("Enter RCPT TO content: ");
                fgets(command, BUFFER_SIZE, stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline character
                break;
            case 4:
                printf("Enter DATA content: ");
                fgets(command, BUFFER_SIZE, stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline character
                break;
            case 5:
                strcpy(command, "QUIT");
                break;
            default:
                printf("Invalid option, try again.\n");
                continue;
        }

        send(client_socket, command, strlen(command), 0);
        recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        printf("Server: %s\n", buffer);

        if (option == 5) {
            close(client_socket);
            printf("Disconnected from server.\n");
            exit(0);
        }
    }

    return 0;
}
