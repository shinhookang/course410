#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    int elem_per_proc = 1;  // Number of elements each process will receive
    int *data = NULL;               // Pointer to the full dataset (only used by root)
    int *recv_data = (int *)malloc(elem_per_proc * sizeof(int)); // Buffer for each process

    if (rank == 0) {
        // Root process initializes the dataset
        data = (int *)malloc(size * elem_per_proc * sizeof(int));
        for (int i = 0; i < size * elem_per_proc; i++) {
            data[i] = i+1;  // Fill the array with sequential values
        }
        printf("Root process data: ");
        for (int i = 0; i < size * elem_per_proc; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    // Scatter the data from the root process to all processes
    MPI_Scatter(data, elem_per_proc, MPI_INT, recv_data, elem_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints its received portion
    printf("Process %d received data: ", rank);
    for (int i = 0; i < elem_per_proc; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    // Clean up
    if (rank == 0) {
        free(data);  // Only root process allocated this array
    }
    free(recv_data);

    MPI_Finalize();
    return 0;
}
