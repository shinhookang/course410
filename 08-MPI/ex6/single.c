#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int provided;

    // Initialize MPI with single-thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    // Check the level of thread support provided
    if (provided != MPI_THREAD_SINGLE) {
        printf("Error: MPI did not provide MPI_THREAD_SINGLE level of thread support.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes

    // Perform a simple task: each process prints its rank
    printf("Hello from process %d out of %d\n", rank, size);

    MPI_Finalize();  // Finalize the MPI environment
    return 0;
}
