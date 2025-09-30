#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_POINTS 1000000  // Number of points per process

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // barrier synchronizes all the processes so they start at about the same time
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time, main_time; 
    start_time = MPI_Wtime();

    int count = 0;
    unsigned int seed = rank;  // Unique seed for each process


    // Use OpenMP to parallelize the Monte Carlo simulation
    #pragma omp parallel reduction(+:count)
    {
        unsigned int local_seed = seed + omp_get_thread_num();
	// distribute the loop across threads
        #pragma omp for 
        for (int i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand_r(&local_seed) / RAND_MAX;
            double y = (double)rand_r(&local_seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                count++;
            }
        }
    } // reduction occurs here 

    // Use MPI_Reduce to gather results from all processes
    int global_count;
    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    main_time = MPI_Wtime() - start_time; 

    // Calculate and print the estimate for π on the root process
    if (rank == 0) {
        double pi_estimate = (4.0 * global_count) / (NUM_POINTS * size);
        printf("Estimated value of Pi: %f\n", pi_estimate);
        printf("Time for work is %lf seconds\n", main_time);
    }

    MPI_Finalize();
    return 0;
}
