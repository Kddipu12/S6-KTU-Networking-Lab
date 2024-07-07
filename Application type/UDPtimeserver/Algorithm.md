### UDP Server Algorithm

**Initialization and Setup**
1. **Include Required Libraries**: Include necessary headers (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `errno.h`, `unistd.h`, `sys/types.h`, `sys/socket.h`, `netinet/in.h`).
2. **Define Constants**: Define `UDP_PORT` and `MAX_BUFFER_SIZE`.
3. **Create Socket**:
   - Call `socket()` with `AF_INET`, `SOCK_DGRAM`, and protocol 0.
   - If the socket creation fails, print an error message and exit.
4. **Setup Server Address**:
   - Initialize `serveraddr` structure to zero using `memset()`.
   - Set `sin_family` to `AF_INET`, `sin_port` to `htons(UDP_PORT)`, and `sin_addr.s_addr` to `htonl(INADDR_ANY)`.
5. **Bind Socket**:
   - Call `bind()` with the server socket and server address.
   - If binding fails, print an error message, close the socket, and exit.

**Main Loop to Handle Requests**
1. **Receive Data**:
   - Enter an infinite loop.
   - Call `recvfrom()` to receive data into `buff` and populate `clientaddr`.
   - If `recvfrom()` fails, print an error message, close the socket, and exit.
   - Null-terminate the received string.
2. **Fork Process**:
   - Call `fork()` to create a child process.
   - If `fork()` fails, print an error message, close the socket, and exit.
   - If in the child process:
     - **Process Request**:
       - If `buff` contains "time":
         - Get the current time using `time()`.
         - Convert it to a readable format using `localtime()` and `strftime()`.
         - Call `sendto()` to send the formatted time back to the client.
         - If `sendto()` fails, print an error message and exit.
         - Print a success message.
       - Close the socket and exit.
3. **Parent Process**:
   - Do nothing (ready to handle the next request).

**Cleanup**
1. **Close Socket**: Close the server socket when done (not reached in this infinite loop).

### UDP Client Algorithm

**Initialization and Setup**
1. **Include Required Libraries**: Include necessary headers (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `errno.h`, `unistd.h`, `sys/types.h`, `sys/socket.h`, `netinet/in.h`, `arpa/inet.h`).
2. **Define Constants**: Define `UDP_PORT` and `MAX_BUFFER_SIZE`.
3. **Create Socket**:
   - Call `socket()` with `AF_INET`, `SOCK_DGRAM`, and protocol 0.
   - If the socket creation fails, print an error message and exit.
4. **Setup Server Address**:
   - Initialize `servaddr` structure to zero using `memset()`.
   - Set `sin_family` to `AF_INET`, `sin_port` to `htons(UDP_PORT)`.
   - Use `inet_aton()` to set `sin_addr` to "127.0.0.1".
   - If `inet_aton()` fails, print an error message, close the socket, and exit.

**Send and Receive Data**
1. **Send Request**:
   - Copy "time" to `buffer`.
   - Call `sendto()` to send `buffer` to the server.
   - If `sendto()` fails, print an error message, close the socket, and exit.
   - Print a success message.
2. **Receive Response**:
   - Call `recvfrom()` to receive data into `buffer`.
   - If `recvfrom()` fails, print an error message, close the socket, and exit.
   - Null-terminate the received string.
   - Print the received system time.

**Cleanup**
1. **Close Socket**: Close the client socket.
