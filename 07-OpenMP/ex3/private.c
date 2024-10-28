#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    int count = 10;

    #pragma omp parallel private(count)
    {
	int thread_id = omp_get_thread_num();
	//count = thread_id * 100;
	printf("Thread ID: %d has count %d in parallel region\n",thread_id, count);
    }

    printf("count: %d\n", count);

    return 0;
}
