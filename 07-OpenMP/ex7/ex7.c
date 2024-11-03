#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int n = 10000;
    int a[n], b[n], c[n], d[n];
    int nthreads=10;

    omp_set_num_threads(nthreads);

    double start_time = omp_get_wtime();

    // Parallelize the first loop
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i * 2;
        //printf("Thread %d: a[%d] = %d, b[%d] = %d \n", omp_get_thread_num(), i, a[i], i, b[i]);
        nthreads = omp_get_num_threads();
    }

    //printf("\n");
    
    // Parallelize the second loop
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
        //printf("Thread %d: c[%d] = %d\n", omp_get_thread_num(), i, c[i]);
    }

    //printf("\n");

    // Parallelize the third loop
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        d[i] = a[i] * b[i];
        //printf("Thread %d: d[%d] = %d\n", omp_get_thread_num(), i, d[i]);
    }

    double end_time = omp_get_wtime();
    double run_time = end_time - start_time;
    printf("Time taken: %.4f seconds\n", run_time);

    printf("Nthreads = %d\n",nthreads);

    return 0;
}
