

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define MATRIX_SIZE 3 //  desired matrix size

typedef struct {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
} shared_mem;

int main() {
    int shmid;
    shared_mem *shm_ptr;
    pid_t pid;
    int i, j, k;

    // Create shared memory segment
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        printf("shmget error");
        exit(1);
    }

    // Attach shared memory segment
    shm_ptr = (shared_mem *) shmat(shmid, NULL, 0);
    if (shm_ptr == (void *) -1) {
        printf("shmat error");
        exit(1);
    }

    // Create child process
    pid = fork();
    if (pid < 0) {
        printf("fork error");
        exit(1);
    } else if (pid == 0) {
    sleep(10);
        // Child process reads matrix A from shared memory
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                printf("Child process reading matrix A[%d][%d]: ", i, j);
                scanf("%d", &shm_ptr->matrix[i][j]);
            }
        }

        // Child process writes matrix B to shared memory
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                printf("Child process writing matrix B[%d][%d]: %d\n", i, j, i+j);
                shm_ptr->matrix[i][j] = i + j; // Assign each element as the sum of its indices
            }
        }

        // Compute matrix D = Q * P
        int matrix_d[MATRIX_SIZE][MATRIX_SIZE];
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                matrix_d[i][j] = 0;
                for (k = 0; k < MATRIX_SIZE; k++) {
                    matrix_d[i][j] += shm_ptr->matrix[i][k] * shm_ptr->matrix[k][j];
                }
            }
        }

        // Write matrix D to shared memory
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                shm_ptr->matrix[i][j] = matrix_d[i][j];
            }
        }

        // Detach shared memory segment
        shmdt((void *) shm_ptr);
        exit(0);
    } else {
        // Parent process writes matrix P to shared memory
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                printf("Parent process writing matrix A[%d][%d]: ", i, j);
                scanf("%d", &shm_ptr->matrix[i][j]);
            }
        }

        // Parent process reads matrix Q from shared memory
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                            printf("Parent process reading matrix B[%d][%d]: %d\n", i, j, shm_ptr->matrix[i][j]);
        }
    }

    // Compute matrix C = Q* P
    int matrix_c[MATRIX_SIZE][MATRIX_SIZE];
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix_c[i][j] = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                matrix_c[i][j] += shm_ptr->matrix[i][k] * shm_ptr->matrix[k][j];
            }
        }
    }

    // Compute matrix D in the child process
    wait(NULL);
    
    // Parent process reads matrix D from shared memory
    int matrix_d[MATRIX_SIZE][MATRIX_SIZE];
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("Parent process reading matrix D[%d][%d]: %d\n", i, j, shm_ptr->matrix[i][j]);
            matrix_d[i][j] = shm_ptr->matrix[i][j];
        }
    }
    // Print matrices P, Q, C, D, 
    printf("Printing  generated matrix P: From the parent process.\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", shm_ptr->matrix[i][j]);
        }
        printf("\n");
    }
    printf("Printing randomly generated matrix Q: From the child process\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix_d[i][j]);
        }
        printf("\n");
    }

    printf("Matrix D=P* Q\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix_d[i][j]);
        }
        printf("\n");
    }

    printf("Matrix C= Q* P\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix_c[i][j]);
        }
        printf("\n");
    }

    

    // Detach and remove shared memory segment
    shmdt((void *) shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}