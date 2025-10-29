#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 1000

int main() {
    int count = 0;

    #pragma omp parallel for 
    for (int i = 0; i < ITERATIONS; i++) {
            count += 1;
    }

    printf("Final sum: %d\n", count);
    printf("Expected sum: %d\n", ITERATIONS);

    return 0;
}