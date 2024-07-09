#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8088
#define BUFFER_SIZE 1024

void reverse_string(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int read_size;

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept client connection
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
        perror("Accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    // Handle client communication
    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[read_size] = '\0';
        
        // Reverse the received string
        reverse_string(buffer);
        
        printf("Received (reversed): %s\n", buffer);

        if (strcmp(buffer, "TIUQ") == 0) {  // Note: "QUIT" reversed
            printf("Client disconnected.\n");
            break;
        } else if (strncmp(buffer, "OLEH", 4) == 0) {  // Note: "HELO" reversed
            send(client_socket, "250 Hello\n", 10, 0);
        } else {
            send(client_socket, "250 OK\n", 7, 0);
        }
    }

    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}
