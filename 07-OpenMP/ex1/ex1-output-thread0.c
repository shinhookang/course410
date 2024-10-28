#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
	int nthread = omp_get_num_threads();
	if (thread_id == 0)
	{
        	printf("I have %d threads. Hello World from thread %d\n", nthread, thread_id);
	}
    }
    return 0;
}
