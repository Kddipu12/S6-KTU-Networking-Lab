### Server Algorithm

1. **Initialize server**:
   - Create a socket using `socket()`.
   - Check for errors in socket creation.
   - Initialize server address structure (`serveraddr`).
   - Set family, port, and IP address.
   - Bind the socket to the specified port using `bind()`.
   - Check for errors in binding.
   - Start listening for incoming connections using `listen()`.

2. **Accept connection**:
   - Accept a client connection using `accept()`.
   - Check for errors in accepting connection.

3. **Handle client requests**:
   - Initialize buffer and filename storage.
   - Loop indefinitely to handle client requests:
     - Clear the buffer.
     - Receive command from client.
     - Check command:
       - **"PUT"**:
         - Clear the buffer and receive filename from client.
         - Open the file for writing.
         - Loop to receive file content from client:
           - Clear the buffer.
           - Receive file content.
           - Check for end of file indicator ("END$").
           - Write content to file.
         - Close the file.
         - Print confirmation of file receipt.
       - **"GET"**:
         - Send server process ID to client.
         - Clear the buffer and receive filename from client.
         - Open the file for reading.
         - Check if file exists:
           - If not, send "404" to client.
           - If exists, send "200" to client.
           - Loop to send file content to client:
             - Clear the buffer.
             - Read content from file.
             - Send content to client.
           - Send end of file indicator ("END$").
           - Close the file.
           - Print confirmation of file sent.
       - **"BYE"**:
         - Close client socket.
         - Close server socket.
         - Exit the program.

### Client Algorithm

1. **Initialize client**:
   - Create a socket using `socket()`.
   - Check for errors in socket creation.
   - Initialize server address structure (`serveraddr`).
   - Set family, port, and IP address.
   - Connect to the server using `connect()`.
   - Check for errors in connection.

2. **Handle user input**:
   - Loop indefinitely to present options to user and handle commands:
     - Print menu and prompt for choice.
     - Read user choice.
     - Check choice:
       - **1. PUT**:
         - Clear the buffer and set command to "PUT".
         - Send command to server.
         - Prompt for filename and read it.
         - Open file for reading.
         - Check if file exists:
           - If not, print error message.
           - If exists, clear buffer and send filename to server.
           - Loop to send file content to server:
             - Read content from file.
             - Send content to server.
             - Clear buffer.
           - Send end of file indicator ("END$").
           - Close the file.
           - Print confirmation of file sent.
       - **2. GET**:
         - Clear the buffer and set command to "GET".
         - Send command to server.
         - Clear the buffer and receive server process ID.
         - Print process ID.
         - Prompt for filename and read it.
         - Clear buffer and send filename to server.
         - Clear buffer and receive response code.
         - Check response code:
           - If "404", print file not found message.
           - If "200", open file for writing.
           - Loop to receive file content from server:
             - Clear buffer.
             - Receive content from server.
             - Check for end of file indicator ("END$").
             - Write content to file.
           - Close the file.
           - Print confirmation of file received.
       - **3. BYE**:
         - Clear buffer and set command to "BYE".
         - Send command to server.
         - Close client socket.
         - Print disconnection message.
         - Exit the program.
       - **Default**:
         - Print invalid choice message.

### Server Algorithm (Detailed Pseudocode)
```
1. Create socket: server_sock = socket(AF_INET, SOCK_STREAM, 0)
2. Check if server_sock < 0:
     Print error message and exit
3. Initialize server address structure (serveraddr)
4. Set serveraddr.sin_family to AF_INET
5. Set serveraddr.sin_port to htons(PORT)
6. Set serveraddr.sin_addr.s_addr to inet_addr("127.0.0.1")
7. Bind socket: bind(server_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr))
8. Check if bind < 0:
     Print error message, close server_sock, and exit
9. Start listening: listen(server_sock, 10)
10. Print "Server is listening on port"
11. Accept connection: client_sock = accept(server_sock, (struct sockaddr *)&clientaddr, &addr_size)
12. Check if client_sock < 0:
     Print error message, close server_sock, and exit
13. Initialize buffer and filename
14. Loop indefinitely:
     Clear buffer
     Receive command: recv(client_sock, buffer, BUFFER_SIZE, 0)
     If command is "PUT":
         Clear buffer
         Receive filename: recv(client_sock, buffer, BUFFER_SIZE, 0)
         Open file for writing: fptr = fopen(filename, "w")
         Check if file opened:
             Print error message and continue
         Loop to receive file content:
             Clear buffer
             Receive content: recv(client_sock, buffer, BUFFER_SIZE, 0)
             Check if content is "END$":
                 Break loop
             Write content to file
         Print "File received"
         Close file
     Else if command is "GET":
         Send process ID to client: send(client_sock, buffer, BUFFER_SIZE, 0)
         Clear buffer
         Receive filename: recv(client_sock, buffer, BUFFER_SIZE, 0)
         Open file for reading: fptr = fopen(filename, "r")
         Check if file opened:
             Send "404" to client
         Else:
             Send "200" to client
             Loop to send file content:
                 Clear buffer
                 Read content from file
                 Send content to client
             Send "END$" to client
             Print "File sent"
             Close file
     Else if command is "BYE":
         Close client_sock and server_sock
         Exit program
```

### Client Algorithm (Detailed Pseudocode)
```
1. Create socket: client_sock = socket(AF_INET, SOCK_STREAM, 0)
2. Check if client_sock < 0:
     Print error message and exit
3. Initialize server address structure (serveraddr)
4. Set serveraddr.sin_family to AF_INET
5. Set serveraddr.sin_port to htons(PORT)
6. Set serveraddr.sin_addr.s_addr to inet_addr("127.0.0.1")
7. Connect to server: connect(client_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr))
8. Check if connect < 0:
     Print error message, close client_sock, and exit
9. Loop indefinitely:
     Print menu and prompt for choice
     Read user choice
     If choice is 1 (PUT):
         Clear buffer
         Set buffer to "PUT"
         Send command to server
         Prompt for filename and read it
         Open file for reading: fptr = fopen(filename, "r")
         Check if file opened:
             Print error message
             Continue
         Clear buffer
         Set buffer to filename
         Send filename to server
         Loop to send file content:
             Read content from file
             Send content to server
             Clear buffer
         Send "END$" to server
         Print "File sent"
         Close file
     Else if choice is 2 (GET):
         Clear buffer
         Set buffer to "GET"
         Send command to server
         Clear buffer
         Receive process ID: recv(client_sock, buffer, BUFFER_SIZE, 0)
         Print process ID
         Prompt for filename and read it
         Clear buffer
         Set buffer to filename
         Send filename to server
         Clear buffer
         Receive response code: recv(client_sock, buffer, BUFFER_SIZE, 0)
         If response code is "404":
             Print "File not found"
         Else if response code is "200":
             Open file for writing: fptr = fopen(filename, "w")
             Check if file opened:
                 Print error message
                 Break
             Loop to receive file content:
                 Clear buffer
                 Receive content: recv(client_sock, buffer, BUFFER_SIZE, 0)
                 Check if content is "END$":
                     Break loop
                 Write content to file
                 Print content
             Print "File received"
             Close file
     Else if choice is 3 (BYE):
         Clear buffer
         Set buffer to "BYE"
         Send command to server
         Close client_sock
         Print "Disconnected from server"
         Exit program
     Else:
         Print "Invalid choice"
```
