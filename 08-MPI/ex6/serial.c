#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int provided, rank, size;

    // Initialize MPI with threading support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
    printf(MPI_THREAD_SERIALIZED);
    printf(provided);

    if (provided < MPI_THREAD_SERIALIZED) {
        printf("MPI does not provide required threading level\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This example requires at least 2 MPI processes\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int data;
    if (rank == 0) {
        data = 42; // Example data to send
    }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Only the master thread (thread 0) performs MPI calls
        if (thread_id == 0) {
            if (rank == 0) {
                MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("MPI Process %d, Thread %d sent data %d\n", rank, thread_id, data);
            } else if (rank == 1) {
                MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("MPI Process %d, Thread %d received data %d\n", rank, thread_id, data);
            }
        }

        // All threads (including master) can do additional work here
        #pragma omp barrier
        printf("MPI Process %d, Thread %d is performing computation\n", rank, thread_id);
    }

    MPI_Finalize();
    return 0;
}

