#include <stdio.h>

int n, i, j, k, dist;

struct matrix {
    int distance;
    int next;
} matrix1[50][50];

void readmatrix() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                printf("Enter the distance from node %d to node %d (if no path, enter 999): ", i + 1, j + 1);
                scanf("%d", &dist);

                matrix1[i][j].distance = dist;
                matrix1[i][j].next = j;
            } else {
                matrix1[i][i].distance = 0;
                matrix1[i][i].next = i;
            }
        }
    }
}

void shortestpath() {
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
}

void displaypath() {
    for (i = 0; i < n; i++) {
        printf("Printing routing table of node %d\n", i + 1);
        printf("Dest \t \t Dist \t \t Next\n");
        for (j = 0; j < n; j++) {
            printf("%d \t \t %d \t \t %d\n", j + 1, matrix1[i][j].distance, matrix1[i][j].next + 1);
        }
    }
}

int main() {
    readmatrix();
    shortestpath();
    displaypath();
    return 0;
}
