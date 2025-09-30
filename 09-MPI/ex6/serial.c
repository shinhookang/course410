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

	// may be needed before the omp single construct that has the MPI call(s)
        #pragma omp barrier
        #pragma omp single
        {
            int send_data = rank * 100;
            int recv_data;

            // Exchange data with the next rank in a ring topology
            int target = (rank + 1) % size;
            int source = (rank - 1 + size) % size;

            MPI_Send(&send_data, 1, MPI_INT, target, 0, MPI_COMM_WORLD);
            MPI_Recv(&recv_data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("(Proc %d, Thread %d): Sent %d to (Proc %d), received %d from (Proc %d)\n",
                   rank, thread_id, send_data, target, recv_data, source);

        }

        // Parallel work for all threads
        printf("(Proc %d, Thread %d) is doing independent work\n", rank, thread_id);
    }

    MPI_Finalize();
    return 0;
}
