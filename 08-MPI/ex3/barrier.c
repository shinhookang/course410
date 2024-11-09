#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Task before the barrier
    printf("Process %d performing task before barrier\n", rank);
    sleep(rank);  

    // MPI_Barrier to synchronize processes
    printf("Process %d waiting at barrier\n", rank);
    MPI_Barrier(MPI_COMM_WORLD);

    // Task after the barrier
    printf("Process %d passed the barrier and continues\n", rank);

    MPI_Finalize();
    return 0;
}
