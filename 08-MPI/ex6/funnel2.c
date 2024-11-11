#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int provided;

    // Initialize MPI with funneled thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    // Check if MPI provided the required level of thread support
    if (provided < MPI_THREAD_FUNNELED) {
        printf("Error: MPI does not support MPI_THREAD_FUNNELED.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Parallel region with OpenMP
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        // Only the main thread (thread 0) makes MPI calls
        if (thread_id == 0) {
            printf("Process %d, Thread %d: Performing MPI call\n", rank, thread_id);
            // Example MPI call
            int data = rank;
            MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
            printf("Process %d received data %d\n", rank, data);
        }

        // All threads can perform computation
        #pragma omp barrier
        printf("Process %d, Thread %d: Performing computation\n", rank, thread_id);
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}
