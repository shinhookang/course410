#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);

    if (provided < MPI_THREAD_SERIALIZED) {
        printf("MPI does not support MPI_THREAD_SERIALIZED level!\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define an OpenMP parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp single
        {
            printf("MPI Rank %d out of %d processes, running %d OpenMP threads\n", rank, size, num_threads);
        }

        // Only the master thread performs MPI communication
        if (thread_id == 0) {
            int data = rank * 100;
            int recv_data;

            // Exchange data with the next rank in a ring topology
            int next_rank = (rank + 1) % size;
            int prev_rank = (rank - 1 + size) % size;

            MPI_Send(&data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
            MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("MPI Rank %d: Sent %d to rank %d, received %d from rank %d\n",
                   rank, data, next_rank, recv_data, prev_rank);
        }

        // Parallel work for all threads
        printf("Rank %d, thread %d is doing independent work\n", rank, thread_id);
    }

    MPI_Finalize();
    return 0;
}
