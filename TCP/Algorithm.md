
---

# Server

1. **Initialise IP address and port number.**
2. **Create a TCP socket using `socket()` system call.**
3. **If `socket()` returns a negative integer, print an error and go to step 14.**
4. **Print "Server socket created!".**
5. **Bind the local address and port using `bind()` system call.**
6. **If `bind()` returns a negative integer, print "bind error" and go to step 14.**
7. **Listen to client using `listen()` system call.**
8. **Accept connection from client using `accept()` system call.**
9. **Print "Client connected".**
10. **Receive message sent by client using `recv()` system call.**
11. **Print the received message.**
12. **Send reply using `send()` system call.**
13. **Close the connection using `close()` system call and go to step 8.**
14. **Exit.**

# Client

1. **Initialise IP address and port number.**
2. **Create a socket using `socket()` system call.**
3. **Print "TCP socket created".**
4. **Connect to the listening socket using `connect()` system call.**
5. **Print "Connected to the server".**
6. **Send a message to the server using `send()` system call.**
7. **Receive reply using `recv()` system call.**
8. **Print the received message.**
9. **Close the connection.**
10. **Print "Disconnected from server".**
11. **Exit.**

---
