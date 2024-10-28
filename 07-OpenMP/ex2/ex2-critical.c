#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 1000

int main() {
    int count = 0;

    #pragma omp parallel for 
    for (int i = 0; i < ITERATIONS; i++) {
        // prevent other threads from modifying count simultaneously.
        // critical applies to entire block of code, allowing only one thread at a time to execute that block.
        #pragma omp critical
        count += 1;
    }

    printf("Final sum: %d\n", count);
    printf("Expected sum: %d\n", ITERATIONS);

    return 0;
}