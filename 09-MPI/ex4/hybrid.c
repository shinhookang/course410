#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000  // Total size of the array on each process

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);  // Initialize MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get MPI rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get number of MPI processes

    double start_time, main_time;
    start_time = MPI_Wtime();

    // Initialize array with values on each MPI process
    double *array = (double *)malloc(ARRAY_SIZE * sizeof(double));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1.0;  // Assign a constant value for simplicity
    }

    // Calculate partial sum using OpenMP on each MPI process
    double local_sum = 0.0;
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += array[i];
    }

    // Print partial sum from each process for verification
    printf("Process %d calculated local sum: %f\n", rank, local_sum);

    // Use MPI_Reduce to get the global sum on root process
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    main_time = MPI_Wtime() - start_time;

    // Root process prints the global sum
    if (rank == 0) {
        printf("Global sum is: %f\n", global_sum);
        printf("Time for work is %lf seconds\n", main_time);
    }

    // Clean up and finalize MPI
    free(array);
    MPI_Finalize();

    return 0;
}
