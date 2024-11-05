#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int message = 42;
    int recvbuf = 0;

    int target_rank = (world_rank+1)%world_size;
    int source_rank = (world_rank-1)%world_size;
    MPI_Send(&message, 1, MPI_INT, target_rank, 0, MPI_COMM_WORLD);
    MPI_Recv(&recvbuf, 1, MPI_INT, source_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    printf("Rank %d received message %d from Rank %d\n",world_rank,recvbuf,source_rank);

    MPI_Finalize();
    return 0;
}
