#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int world_rank;
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank (ID) of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the total number of processes

    // Print a "Hello, World!" message from each process
    printf("Hello, World! from process %d of %d\n", world_rank, world_size);

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
