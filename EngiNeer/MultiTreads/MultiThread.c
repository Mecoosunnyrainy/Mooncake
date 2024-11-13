#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int m, n, p; // Matrix A dimensions (m x n) and Matrix B dimensions (n x p)

// Structure to pass data to each thread
typedef struct {
    int row;
} ThreadData;

// Thread function to calculate a row of the result matrix
void* multiply_row(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;

    for (int i = 0; i < p; i++) {
        C[row][i] = 0; // Initialize result cell
        for (int j = 0; j < n; j++) {
            C[row][i] += A[row][j] * B[j][i];
        }
    }

    pthread_exit(0);
}

int main() {
    printf("Enter dimensions of matrix A (rows columns): ");
    scanf("%d %d", &m, &n);

    printf("Enter dimensions of matrix B (rows columns): ");
    scanf("%d %d", &n, &p);

    if (n != n) {
        printf("Matrices cannot be multiplied!\n");
        return 1;
    }

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    pthread_t threads[m];
    ThreadData thread_data[m];

    // Create threads to calculate each row of the result matrix
    for (int i = 0; i < m; i++) {
        thread_data[i].row = i;
        pthread_create(&threads[i], NULL, multiply_row, (void*)&thread_data[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix C
    printf("Result matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
