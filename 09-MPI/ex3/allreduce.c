#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    // Each process has its rank as local data
    int local_data = 1;

    // Variable to store the result of the reduction on each process
    int global_sum = 0;

    // Perform the all-reduction operation (sum), making the result available on all processes
    MPI_Allreduce(&local_data, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Each process prints the result
    printf("Process %d received the sum of ranks: %d\n", rank, global_sum);

    MPI_Finalize();
    return 0;
}
