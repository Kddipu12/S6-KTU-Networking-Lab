# Generalized Algorithm for Stop-and-Wait ARQ

## Server Side

### 1. Initialize Server
- **Input**: IP address, port number.
- **Output**: UDP socket for communication.
- **Steps**:
  1. Create a UDP socket.
  2. Initialize the server address structure with the given IP address and port number.
  3. Bind the socket to the server address.

### 2. Listen for Incoming Packets
- **Input**: Initialized server socket.
- **Output**: Received packets and acknowledgment (ACK) responses.
- **Steps**:
  1. Initialize a variable to track the expected sequence number (initially set to 0).
  2. Enter an infinite loop to continuously listen for incoming packets.
  3. Clear the buffer to receive the packet.
  4. Receive a packet from the client.
  5. Extract the sequence number from the received packet.
  6. If the sequence number matches the expected sequence number:
     - Print the received packet number.
     - Randomly decide whether to send an acknowledgment.
     - If sending an acknowledgment:
       - Send the acknowledgment packet back to the client.
       - Increment the expected sequence number.
  7. If the sequence number does not match the expected sequence number:
     - Print that a duplicate packet was received.

### 3. Terminate
- **Input**: None.
- **Output**: None.
- **Steps**:
  1. Close the server socket when terminating the server (should be included for graceful shutdown).

## Client Side

### 1. Initialize Client
- **Input**: IP address, port number.
- **Output**: UDP socket for communication.
- **Steps**:
  1. Create a UDP socket.
  2. Initialize the server address structure with the given IP address and port number.

### 2. Send Packets and Wait for Acknowledgments
- **Input**: Initialized client socket.
- **Output**: Sent packets and received acknowledgments.
- **Steps**:
  1. Initialize a variable to track the packet sequence number (initially set to 1).
  2. Enter a loop to send packets up to a specified limit.
  3. For each packet:
     - Clear the buffer.
     - Format the packet with the current sequence number.
     - Print the sending packet number.
     - Send the packet to the server.
     - Set a timeout for receiving an acknowledgment.
     - Clear the buffer for receiving the acknowledgment.
     - Attempt to receive the acknowledgment within the timeout period.
     - If an acknowledgment is received:
       - Print that the acknowledgment was received.
       - Increment the sequence number.
     - If an acknowledgment is not received (timeout occurs):
       - Print a timeout error message.
       - Resend the same packet.

### 3. Terminate
- **Input**: None.
- **Output**: None.
- **Steps**:
  1. Close the client socket when done sending packets.

