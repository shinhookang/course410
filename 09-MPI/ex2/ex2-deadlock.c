#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int message = 42;

    if (world_rank == 0) {
        // Rank 0 tries to receive a message from Rank 1 and send a message to Rank 1
        MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 received message from Rank 1\n");
    } else if (world_rank == 1) {
        // Rank 1 tries to receive a message from Process 0 and send a message to Rank 0
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Rank 1 received message from Rank 0\n");
    }

    MPI_Finalize();
    return 0;
}
