#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int count=0, provided;
    int rank;
    

    // Initialize MPI with funneled thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Master thread makes all MPI calls
    #pragma omp parallel reduction(+:count)
    {
      #pragma omp for 
      for (int i = 0; i < 100; i++) {
        count++;
      }
    }
    //#pragma omp parallel for reduction(+:count)
    //for (int i = 0; i < 100; i++) {
    //  count++;
    //}
            
    printf("Process %d counts: %d\n", rank, count);


    MPI_Finalize();
    return 0;
}

