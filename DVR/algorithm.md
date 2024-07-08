To write an algorithm for a 30-mark question based on the given C program, you need to provide a detailed, step-by-step explanation of how the program works. Here's a comprehensive algorithm for the multi-node routing table calculation program:

### Algorithm

#### 1. **Initialize and Read Matrix:**
   - **Step 1:** Initialize variables:
     - `n`: Number of nodes.
     - `i, j, k`: Loop counters.
     - `dist`: Distance between nodes.
     - `matrix1[50][50]`: A 2D array of structures to store distance and next hop information.

   - **Step 2:** Define the structure `matrix`:
     ```c
     struct matrix {
         int distance;
         int next;
     } matrix1[50][50];
     ```

   - **Step 3:** Read the number of nodes:
     ```c
     printf("Enter the number of nodes: ");
     scanf("%d", &n);
     ```

   - **Step 4:** For each pair of nodes `(i, j)`:
     - If `i` is not equal to `j`, prompt the user to enter the distance between node `i` and node `j`:
       ```c
       printf("Enter the distance from node %d to node %d (if no path, enter 999): ", i + 1, j + 1);
       scanf("%d", &dist);
       ```
     - Set the distance and next hop for the pair:
       ```c
       matrix1[i][j].distance = dist;
       matrix1[i][j].next = j;
       ```
     - If `i` is equal to `j`, set the distance to `0` and next hop to `i`:
       ```c
       matrix1[i][i].distance = 0;
       matrix1[i][i].next = i;
       ```

#### 2. **Compute Shortest Paths (Floyd-Warshall Algorithm):**
   - **Step 5:** For each pair of nodes `(i, j)`:
     - Iterate over all possible intermediate nodes `k`:
       ```c
       for (i = 0; i < n; i++) {
           for (j = 0; j < n; j++) {
               for (k = 0; k < n; k++) {
                   if (matrix1[i][j].distance > (matrix1[i][k].distance + matrix1[k][j].distance)) {
                       matrix1[i][j].distance = matrix1[i][k].distance + matrix1[k][j].distance;
                       matrix1[i][j].next = k;
                   }
               }
           }
       }
       ```
     - If the distance through node `k` is shorter, update the distance and next hop for the pair `(i, j)`:
       ```c
       if (matrix1[i][j].distance > (matrix1[i][k].distance + matrix1[k][j].distance)) {
           matrix1[i][j].distance = matrix1[i][k].distance + matrix1[k][j].distance;
           matrix1[i][j].next = k;
       }
       ```

#### 3. **Display Routing Tables:**
   - **Step 6:** For each node `i`, print the routing table:
     - Print the header:
       ```c
       printf("Printing routing table of node %d\n", i + 1);
       printf("Dest \t \t Dist \t \t Next\n");
       ```
     - For each destination node `j`, print the destination, distance, and next hop:
       ```c
       for (j = 0; j < n; j++) {
           printf("%d \t \t %d \t \t %d\n", j + 1, matrix1[i][j].distance, matrix1[i][j].next + 1);
       }
       ```

### Detailed Steps in Program:

#### Main Function:
   - **Step 7:** Call the `readmatrix()` function to initialize the distance matrix.
   - **Step 8:** Call the `shortestpath()` function to compute the shortest paths using the Floyd-Warshall algorithm.
   - **Step 9:** Call the `displaypath()` function to display the routing tables of all nodes.

