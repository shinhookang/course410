#include <stdio.h>
#include <omp.h>

#define NTIMES 16 // total number of measures
#define ARRAY_SIZE 80000
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];

int main() {

    double start_time, end_time, run_time=0.;
    
    #pragma omp parallel
    {
        int tid = omp_get_thread_num(); // thread id

        if (tid == 0) {
            printf("Nthreads: %d \n", omp_get_num_threads());       
            start_time = omp_get_wtime();
        }

        #pragma omp for
        for (int i=0; i<ARRAY_SIZE; i++){
            a[i] = 1.0;
            b[i] = 2.0;
        }

        double m = 3.0;
        for (int iter=0; iter<ARRAY_SIZE; iter++){
            
            #pragma omp for
            for (int i=0; i<ARRAY_SIZE; i++){
                c[i] = a[i] + m * b[i];
            }

            if (tid == 0) {
                end_time = omp_get_wtime();
                run_time += end_time - start_time;
                start_time = end_time;
                //printf("Time taken: %.6f seconds\n", run_time);
            }
            c[1] = c[2];
        }
        
    }
    printf("Time taken: %.6f seconds\n", run_time/NTIMES);       

    

    // double sum = 0.0;
    // #pragma omp parallel for reduction(+:sum)
    // for (int i=0; i<ARRAY_SIZE; i++)
    // {
	// sum = sum + a[i] + b[i]; 		
    // }

    // printf("sum = %g\n", sum);
    
    return 0;
}
