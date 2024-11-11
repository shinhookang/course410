#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int provided;

    // Initialize MPI with serialized thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);

    // Check the provided thread support level
    if (provided < MPI_THREAD_SERIALIZED) {
        printf("Error: MPI does not support MPI_THREAD_SERIALIZED.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Parallel region with OpenMP
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        // Each thread tries to make an MPI call, but only one at a time
        #pragma omp critical  // Ensures only one thread enters this section at a time
        {
            printf("(Proc %d, Thread %d): Performing MPI call\n", rank, tid);
            
            int data = rank * 10 + tid;
            // Example MPI call (broadcasting data)
            MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
            printf("(Proc %d, Thread %d) received data %d\n", rank, tid, data);
        }

        // Other work that does not involve MPI
        printf("(Proc %d, Thread %d): Performing computation\n", rank, tid);
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}
