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

    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i<ARRAY_SIZE; i++)
    {
	sum = sum + a[i] + b[i]; 		
    }

    printf("sum = %g\n", sum);
    
    return 0;
}
