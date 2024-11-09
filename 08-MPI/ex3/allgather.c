#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    // Each process calculates a local data value
    int local_data = rank;

    // Allocate an array to receive the gathered data on each process
    int *gathered_data = (int *)malloc(size * sizeof(int));
    if (gathered_data == NULL) {
        perror("Failed to allocate memory for gathered data");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Use MPI_Allgather to gather data from each process into gathered_data
    MPI_Allgather(&local_data, 1, MPI_INT, gathered_data, 1, MPI_INT, MPI_COMM_WORLD);

    // Print the gathered data on each process
    printf("Process %d received gathered data: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", gathered_data[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(gathered_data);
    MPI_Finalize();
    return 0;
}
