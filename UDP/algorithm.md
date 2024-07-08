### Server Algorithm

1. **Initialize Variables:**
   - Define server IP address (`ip`) and port (`port`).
   - Declare variables for socket file descriptor (`sockfd`), server address structure (`server_addr`), client address structure (`client_addr`), message buffer (`buffer`), address size (`addr_size`), and return value (`n`).

2. **Create Socket:**
   - Use `socket` to create a UDP socket. If the socket creation fails, print an error message and exit.

3. **Configure Server Address:**
   - Set the address family to `AF_INET`.
   - Set the server port using `htons(port)`.
   - Set the server IP address using `inet_addr(ip)`.

4. **Bind Socket:**
   - Bind the socket to the server address using `bind`. If binding fails, print an error message and exit.

5. **Receive Data:**
   - Clear the message buffer using `bzero`.
   - Initialize the client address size (`addr_size`).
   - Use `recvfrom` to receive data from the client. Store the received data in the buffer and the client's address in `client_addr`.

6. **Process Data:**
   - Print the received data.
   - Prepare a response message and store it in the buffer.

7. **Send Response:**
   - Use `sendto` to send the response message to the client.

8. **Exit Program:**
   - Close the socket and exit the program.

### Client Algorithm

1. **Initialize Variables:**
   - Define server IP address (`ip`) and port (`port`).
   - Declare variables for socket file descriptor (`sockfd`), server address structure (`addr`), message buffer (`buffer`), and address size (`addr_size`).

2. **Create Socket:**
   - Use `socket` to create a UDP socket. If the socket creation fails, print an error message and exit.

3. **Configure Server Address:**
   - Set the address family to `AF_INET`.
   - Set the server port using `htons(port)`.
   - Set the server IP address using `inet_addr(ip)`.

4. **Get User Input:**
   - Clear the message buffer using `bzero`.
   - Prompt the user to enter data and store it in the buffer.

5. **Send Data:**
   - Use `sendto` to send the user input data to the server.

6. **Receive Response:**
   - Clear the message buffer using `bzero`.
   - Initialize the server address size (`addr_size`).
   - Use `recvfrom` to receive the response message from the server and store it in the buffer.

7. **Print Response:**
   - Print the received response message.

8. **Exit Program:**
   - Close the socket and exit the program.
