#include <stdio.h>
#include <omp.h>

int main() {
	omp_set_num_threads(3);
    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
	int nthread = omp_get_num_threads();
        printf("I have %d threads. Hello World from thread %d\n", nthread, thread_id);
    }
    return 0;
}
