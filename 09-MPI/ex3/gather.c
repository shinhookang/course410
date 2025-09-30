#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    // Each process calculates its result 
    int local_data = rank;

    // Array to hold the gathered data on the root process
    int *gathered_data = NULL;
    if (rank == 0) {
        gathered_data = (int *)malloc(size * sizeof(int));
        if (gathered_data == NULL) {
            perror("Failed to allocate memory for gathered data");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Gather local_data from each process to the root process
    MPI_Gather(&local_data, 1, MPI_INT, gathered_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process prints the gathered results
    if (rank == 0) {
        printf("Gathered data on root process:\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d squared: %d\n", i, gathered_data[i]);
        }
        free(gathered_data);  // Free memory on the root process
    }

    MPI_Finalize();
    return 0;
}
