#include <stdio.h>
#include <omp.h>
// - - - NOT READY YET - - - 
void prefix_scan(int *input, int *output, int n) {
    
    #pragma omp parallel
    {

        // Determine lower and uppper thread bounds 
        int nthreads = omp_get_num_threads(); // nthreads
        int tid = omp_get_thread_num(); // thread id
        long int nelem_p = n/nthreads;    
        long int ltb = nelem_p*tid; // lower thread bound
        long int utb = nelem_p*(tid+1); // upper thread bound
        if (tid == nthreads-1){
            utb = n;
        }

        if (tid == 0) {
            printf("Nthreads: %d \n", omp_get_num_threads());
        }

        long int *offset = (long int *)malloc(nthreads * sizeof(long int));
            

        // Step 1: Copy the input array into the output array as the initial state
        for (int i = ltb; i < utb; i++) {
            output[i] = input[i];
        }

        // Step 2: perform prefix scan on each thread, start from ltb+1
        for (int i = ltb+1; i < utb; i++) {
            output[i] = output[i - 1] + input[i];
        }

        // Step 3: Compute offset for each thread at master thread
        #pragma omp barrier
        if (tid == 0){
            printf("offset: \n");
            offset[0] = 0.;
            for (int i=1; i<nthreads; i++){

                long int _ltb = nelem_p*i; // lower thread bound
                long int _utb = nelem_p*(i+1); // upper thread bound

                offset[i] = output[_utb-1];
                printf("offset[%d]: %ld \n",i, offset[i]);
            }
            // for (int i = 0; i < nthreads; i++) {
            //     output[i] = output[i - 1] + input[i];
            //     output[i] = output[i - 1] + input[i];
            // }    
        }
        // for (int i = ltb; i < utb; i++) {
        //     output[i] = output[i - 1] + input[i];
        // }

    }
        

}

int main() {
    int n = 10;
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int output[n];

    prefix_scan(input, output, n);

    // Print the results
    printf("Prefix Sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
