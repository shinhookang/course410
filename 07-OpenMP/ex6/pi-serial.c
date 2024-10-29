#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define NUM_POINTS 1000000000

int main() {
    long long int count = 0;
    double pi, x, y;
    int num_threads;

    double start_time = omp_get_wtime();

    unsigned int seed = (unsigned int)time(NULL); 

    for (long long int i = 0; i < NUM_POINTS; i++) 
    {
       x = (double)rand_r(&seed) / RAND_MAX;
       y = (double)rand_r(&seed) / RAND_MAX;
       if (x*x + y*y <= 1) count++;
    }

    pi = 4.0 * count / NUM_POINTS;

    double end_time = omp_get_wtime();
    double run_time = end_time - start_time;

    printf("True Pi:      %.15f\n", M_PI);
    printf("Estimated Pi: %.15f\n", pi);
    printf("Difference: %.15g\n", pi-M_PI);
    printf("Time taken: %.4f seconds\n", run_time);

    return 0;
}
