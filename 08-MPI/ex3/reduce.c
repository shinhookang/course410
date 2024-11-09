#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    // Each process has its rank as local data
    int local_data = 1;

    // Variable to store the result of the reduction on the root process
    int global_sum = 0;

    // Perform the reduction operation (sum) and store the result on the root process
    MPI_Reduce(&local_data, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the result
    if (rank == 0) {
        printf("Sum of ranks across all processes: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
