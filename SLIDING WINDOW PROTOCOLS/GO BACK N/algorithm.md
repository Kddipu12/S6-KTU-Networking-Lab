# Server Algorithm

1. **Start Server Program**
   - Initialize necessary variables: server socket, client socket, message buffers, file descriptor set, server address structure, client address structure, and timeout structure.

2. **Create Server Socket**
   - Use `socket` with parameters for a TCP socket.

3. **Initialize Server Address Structure**
   - Set address family to `AF_INET`, port number to `7004`, and IP address to `INADDR_ANY`.

4. **Bind Server Socket**
   - Bind the server socket to the server address using `bind`.
   - If binding fails, print an error and exit.

5. **Set Server to Listen**
   - Use `listen` with a backlog of 5.
   - Print a ready message.

6. **Accept Incoming Connection**
   - Use `accept` to accept an incoming connection from a client.
   - If the accept call fails, print an error and exit.

7. **Initialize Frame Counter and Buffers**
   - Initialize frame counter and message buffers.
   - Clear and prepare the write buffer.

8. **Label Zero**
   - Increment frame counter by 1.
   - Clear write buffer, construct message, and append frame number.
   - Send message to receiver and print frame number sent.
   - Increment frame counter by 1 and sleep for 1 second.

9. **Label One**
   - Clear write buffer, construct message, and append frame number.
   - Send message to receiver and print frame number sent.

10. **Monitor Client Socket Using `select`**
    - Clear file descriptor set and add client socket.
    - Set timeout period to 2 seconds.
    - Use `select` to wait for data on the client socket.

11. **Handle Result of `select`**
    - If error, print error message.
    - If timeout, print timeout message, decrement frame counter, and resend from last successfully sent packet by jumping to label zero.
    - If acknowledgment received, read acknowledgment, print details, increment frame counter, and check if all frames are acknowledged. If so, exit.
    - Handle special conditions by adjusting frame counter and resending packets if needed.

12. **Close Sockets**
    - Close client and server sockets after all frames are sent and acknowledged.
    
13. **Exit Program**
    - Exit the program.

# Client Algorithm

1. **Start Client Program**
   - Initialize necessary variables: client socket, frame counter, flag for simulating packet loss, message buffers, and client address structure.

2. **Create Client Socket**
   - Use `socket` with parameters for a TCP socket.

3. **Initialize Client Address Structure**
   - Set address family to `AF_INET`, port number to `7004`, and IP address to `127.0.0.1`.

4. **Connect to Server**
   - Use `connect` to connect the client socket to the server.
   - If connection fails, print an error and exit.

5. **Print Ready Message**
   - Indicate the client is ready.

6. **Loop to Receive and Acknowledge Frames**
   - Loop for 8 iterations:
     - Clear the read buffer and write buffer.
     - Simulate packet loss by skipping the read for frame 5 if the flag is set. Set the flag to avoid skipping again.
     - Read the frame from the server.
       - If the frame number is out of order, print a message indicating packet loss and discard the frame by decrementing the frame counter.
       - If the frame number is in order, print the received frame.
       - Handle special cases for additional reads and frame counter adjustments.
     - Determine the acknowledgment number based on the current frame.
     - Print acknowledgment details, distinguishing between cumulative and individual acknowledgments.
     - Copy the acknowledgment message into the write buffer, append the acknowledgment number, and send it to the server.

7. **Close Client Socket**
   - Close the client socket after all frames are received and acknowledged.

8. **Exit Program**
   - Exit the program.
