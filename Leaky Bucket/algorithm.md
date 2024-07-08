### Algorithm for Leaky Bucket Simulation

#### Input:
- `rate`: Output transmission rate (in bytes per time unit).
- `bucketSize`: Size of the leaky bucket (in bytes).

#### Variables:
- `packets[]`: Array to hold the size of incoming packets.
- `packetCount`: Total number of packets.
- `remainingSize`: Amount of data remaining in the bucket.
- `timeToTransmit`: Time left for transmission.
- `op`: Size of the transmitted packet.

#### Steps:

1. **Initialize and Seed Random Generator:**
    - Initialize the random number generator with the current time for random packet size generation.
    
2. **Generate Random Packet Sizes:**
    - For each packet, generate a random size between 10 and 60 bytes (inclusive).

3. **Input Rate and Bucket Size:**
    - Prompt the user to input the output transmission rate and the bucket size.

4. **Simulation Loop:**
    - Initialize the packet index `i` to 0 and `remainingSize` to 0.
    - While there are packets to process or data remaining in the bucket:
        1. **Process Incoming Packet:**
            - If the current packet's size plus the remaining size exceeds the bucket size, drop the packet.
            - Otherwise, add the packet size to the remaining size.
            - Print the size of the incoming packet and the bytes remaining to transmit.
        
        2. **Determine Transmission Time:**
            - Randomly set the time to transmit between 10 and 40 time units.
            - Print the time left for transmission.

        3. **Transmit Data:**
            - For every 10 units of time until the transmission time is exhausted:
                - Simulate the passage of time with a 1-second delay.
                - If there is data remaining to transmit:
                    - If the remaining data is less than or equal to the transmission rate, transmit all remaining data.
                    - Otherwise, transmit data equal to the transmission rate.
                    - Print the size of the transmitted packet and the bytes remaining to transmit.
                - If no data is left to transmit, print the time left for transmission and that there are no packets to transmit.
        4. **Move to Next Packet:**
            - Increment the packet index.

5. **End of Simulation:**
    - When all packets are processed and no data remains in the bucket, end the simulation.

#### Example of Use:

```plaintext
Enter the output rate: 30
Enter the bucket size: 50

Incoming Packet size: 40
Bytes remaining to Transmit: 40
Time left for transmission: 30 units

Packet transmitted: 30 bytes
Bytes Remaining to Transmit: 10

Packet transmitted: 10 bytes
Bytes Remaining to Transmit: 0

Time left for transmission: 0 units
No packets to transmit
...
```

This algorithm represents the logic and flow of the provided C program, simulating the leaky bucket algorithm for network traffic shaping.
