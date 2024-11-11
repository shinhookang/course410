#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int provided;

    // Initialize MPI with full multi-threading support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    // Check if MPI provided the required level of thread support
    if (provided < MPI_THREAD_MULTIPLE) {
        printf("Error: MPI does not support MPI_THREAD_MULTIPLE.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This example requires at least 2 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    #pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        int data = rank * 100 + tid; // Unique data for each thread

        if (rank == 0) {
            // Thread on process 0 sends a data to the corresponding thread on process 1
            MPI_Send(&data, 1, MPI_INT, 1, tid, MPI_COMM_WORLD);
            printf("Process 0, Thread %d sent data: %d to Process 1, Thread %d\n", tid, data, tid);
        } else if (rank == 1) {
            // Thread on process 1 receives a data from the corresponding thread on process 0
            MPI_Recv(&data, 1, MPI_INT, 0, tid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 1, Thread %d received data: %d from Process 0, Thread %d\n", tid, data, tid);
        }
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}
