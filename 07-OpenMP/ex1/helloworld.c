#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello World from thread %d\n", thread_id);
    }
    return 0;
}
