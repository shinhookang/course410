#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 80000
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];

void vector_add(double *c, double *a, double *b, int n);

int main() {

    for (int i=0; i<ARRAY_SIZE; i++)
    {
	a[i] = 1.0;
	b[i] = 2.0;
    }

    #pragma omp parallel 
    {
	int nthread = omp_get_num_threads();
	int thread_id = omp_get_thread_num();
	printf("Thread ID: %d / total %d threads \n", thread_id, nthread);

	#pragma omp for 
	for (int i=0; i<ARRAY_SIZE; i++)
	{
		c[i] = a[i] + b[i]; 		
	}
    }

    double sum = 0.0;
    for (int i=0; i<ARRAY_SIZE; i++)
    {
	    sum = sum + c[i];
    }

	printf("sum = %g\n", sum);
    
    return 0;
}
