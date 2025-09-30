#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);  // Initialize the MPI environment

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    int data=0;
    if (rank == 0) {
        // Root process initializes the data
        data = 1;
        printf("Process %d (root) broadcasting data %d\n", rank, data);
    }

    // Broadcast data from process 0 to all other processes
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // All processes receive the broadcasted data
    printf("Process %d received data %d\n", rank, data);

    MPI_Finalize();  // Finalize the MPI environment
    return 0;
}
