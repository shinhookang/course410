#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int message = 42;

    MPI_Request request; 

    if (world_rank == 0) {
        // Rank 0 initiates a non-blocking send to Rank 1
        MPI_Isend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        // Wait for send to complete
        MPI_Wait(&request, MPI_STATUS_IGNORE); 
        printf("Rank 0 sent a message to Rank 1\n");
    } else if (world_rank == 1) {
        // Rank 1 initiates a non-blocking receive from Rank 0
        MPI_Irecv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        // Wait for receive to complete
        MPI_Wait(&request, MPI_STATUS_IGNORE); 
        printf("Rank 1 received a message from Rank 0\n");
    }

    MPI_Finalize();
    return 0;
}
