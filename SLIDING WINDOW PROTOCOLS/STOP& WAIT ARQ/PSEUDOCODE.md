To ensure the pseudocode is comprehensive enough for a 30-mark question, we should expand it to include more details about the initialization, error handling, and operations performed. Here is a more detailed version of the pseudocode for both the server and client, emphasizing clarity and completeness.

---

### Pseudocode for Server

1. **Initialize the server:**
    - Set the server IP address (`127.0.0.1`) and port number (`5579`).
    - Seed the random number generator with the current time using `srand(time(0))`.
    - Create a socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
    - If the socket creation fails, print "Socket error" and exit.
    - Print "Successfully created socket" if socket creation is successful.

2. **Configure the server address:**
    - Initialize the `server_addr` structure with zeros.
    - Set the address family to `AF_INET`.
    - Set the port number using `htons(port)`.
    - Set the IP address to `INADDR_ANY` using `htonl(INADDR_ANY)`.

3. **Bind the socket to the server address:**
    - Use `bind` to bind the socket to the server address.
    - If binding fails, print "Bind error" and exit.

4. **Initialize variables:**
    - Set `expectedSeqNum` to 0.
    - Define `buffer` and `recvSeqNum`.

5. **Main server loop:**
    - Continuously listen for incoming packets:
        - Clear the `buffer` using `bzero`.
        - Receive a message from a client using `recvfrom`, storing the client address in `client_addr`.
        - Extract the sequence number from the received message and store it in `recvSeqNum` using `atoi(buffer)`.
        - If `recvSeqNum` equals `expectedSeqNum`:
            - Print "Server: Received packet `recvSeqNum`".
            - Randomly decide whether to send an acknowledgment (50% chance):
                - If acknowledgment is to be sent, print "Server: Sending acknowledgment for packet `recvSeqNum`".
                - Send the acknowledgment back to the client using `sendto`.
                - Increment `expectedSeqNum`.
        - If `recvSeqNum` does not equal `expectedSeqNum`, print "Server: Received duplicate packet `recvSeqNum`".

---

### Pseudocode for Client

1. **Initialize the client:**
    - Set the server IP address (`127.0.0.1`) and port number (`5579`).
    - Create a socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
    - If the socket creation fails, print "Socket error" and exit.
    - Print "Successfully created socket" if socket creation is successful.

2. **Configure the server address:**
    - Initialize the `addr` structure with zeros.
    - Set the address family to `AF_INET`.
    - Set the port number using `htons(port)`.
    - Set the IP address using `inet_addr(ip)`.

3. **Initialize variables:**
    - Set `packetCounter` to 0.
    - Define `buffer` and `addr_size`.

4. **Main client loop:**
    - Loop while `packetCounter` is less than 7:
        - Clear the `buffer` using `bzero`.
        - Format the packet with the current `packetCounter` using `sprintf`.
        - Print "Client: Sending packet `packetCounter`".
        - Send the packet to the server using `sendto`.
        - Set the socket timeout value to `TIMEOUT_VALUE` seconds using `setsockopt`.
        - Clear the `buffer` using `bzero`.
        - Attempt to receive an acknowledgment from the server using `recvfrom`:
            - If a timeout occurs, print "Client: Timeout error! Sending packet `packetCounter` again".
            - If an acknowledgment is received, print "Client: Received acknowledgment for packet `packetCounter`" and increment `packetCounter`.
        - Wait for 1 second using `sleep(1)`.

5. **Close the socket:**
    - Close the socket using `close(sockfd)`.

---

### Expanded Detailed Pseudocode

#### Server Pseudocode

```pseudo
Initialize server IP to "127.0.0.1"
Initialize port to 5579
Seed random number generator with current time
Create UDP socket
If socket creation fails, print "Socket error" and exit
Print "Successfully created socket"

Initialize server address structure to zero
Set address family to AF_INET
Set port using htons(port)
Set IP address to INADDR_ANY using htonl(INADDR_ANY)

Bind socket to server address
If binding fails, print "Bind error" and exit

Set expectedSeqNum to 0

Loop forever
    Clear buffer to zero
    Receive message from client, store client address
    Extract sequence number from received message using atoi(buffer)
    If received sequence number equals expectedSeqNum
        Print "Server: Received packet" with sequence number
        Randomly decide to send acknowledgment (50% chance)
        If sending acknowledgment
            Print "Server: Sending acknowledgment for packet" with sequence number
            Send acknowledgment to client
            Increment expectedSeqNum
    Else
        Print "Server: Received duplicate packet" with sequence number
End Loop
```

#### Client Pseudocode

```pseudo
Initialize server IP to "127.0.0.1"
Initialize port to 5579
Create UDP socket
If socket creation fails, print "Socket error" and exit
Print "Successfully created socket"

Initialize server address structure to zero
Set address family to AF_INET
Set port using htons(port)
Set IP address using inet_addr(ip)

Set packetCounter to 0

Loop while packetCounter < 7
    Clear buffer to zero
    Format packet with current packetCounter using sprintf
    Print "Client: Sending packet" with packetCounter
    Send packet to server using sendto
    Set socket timeout to TIMEOUT_VALUE seconds using setsockopt
    Clear buffer to zero
    Try to receive acknowledgment from server using recvfrom
    If timeout occurs
        Print "Client: Timeout error! Sending packet" with packetCounter "again"
    Else
        Print "Client: Received acknowledgment for packet" with packetCounter
        Increment packetCounter
    Wait for 1 second using sleep(1)
End Loop

Close socket using close(sockfd)
```

---

