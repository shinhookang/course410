#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int n = 100000;
    int a[n], b[n], c[n], d[n];
    int nthreads=10;

    omp_set_num_threads(nthreads);

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        // Determine lower and uppper thread bounds 
        int nelem_p = n/nthreads;
        // printf("nelem_per_thread = %d\n", nelem_p);

        int tid = omp_get_thread_num(); // thread id
        int ltb = nelem_p*tid; // lower thread bound
        int utb = nelem_p*(tid+1); // upper thread bound
        if (tid == nthreads-1){
            utb = n;
        }
        printf("Thread %d: ltb = %d, utb = %d \n", tid, ltb, utb);

        // The first loop
        for (i = ltb; i < utb; i++) {
            a[i] = i;
            b[i] = i * 2;
            //printf("Thread %d: a[%d] = %d, b[%d] = %d \n", tid, i, a[i], i, b[i]);
        }   
        
        //printf("\n");

        // The second loop
        for (i = ltb; i < utb; i++) {
            c[i] = a[i] + b[i];
            //printf("Thread %d: c[%d] = %d\n", tid, i, c[i]);
        }

        //printf("\n");

        // The third loop
        for (i = ltb; i < utb; i++) {
            d[i] = a[i] * b[i];
            //printf("Thread %d: d[%d] = %d\n", tid, i, d[i]);
        }

    }

    double end_time = omp_get_wtime();
    double run_time = end_time - start_time;
    printf("Time taken: %.4f seconds\n", run_time);

    printf("Nthreads = %d\n",nthreads);

    return 0;
}
