#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void prefix_scan(int *input, int *output, int n) {
    
    #pragma omp parallel
    {

        // Determine lower and uppper thread bounds 
        int nthreads = omp_get_num_threads(); // nthreads
        if (nthreads>n){
            printf("[%d]threads should be smaller than %d\n",nthreads,n);
            exit(0);
        }
        int tid = omp_get_thread_num(); // thread id
        long int nelem_p = n/nthreads;    
        long int ltb = nelem_p*tid; // lower thread bound
        long int utb = nelem_p*(tid+1); // upper thread bound
        if (tid == nthreads-1){
            utb = n;
        }
        printf("Thread %d: ltb = %ld, utb = %ld \n", tid, ltb, utb);
        
        if (tid == 0) {
            printf("Nthreads: %d \n", omp_get_num_threads());
        }

        //long int *offset = (long int *)malloc(nthreads * sizeof(long int));
            

        // Step 1: Copy the input array into the output array as the initial state
        output[ltb] = 0.;
        for (int i = ltb+1; i < utb; i++) {
            output[i] = input[i];
        }

        // Step 2: perform prefix scan on each thread, start from ltb+1
        for (int i = ltb+1; i < utb; i++) {
            output[i] = output[i - 1] + input[i];
        }

        // Step 3: Compute offset for each thread at master thread
        #pragma omp barrier
        // if (tid==2){
        //     for (int i=ltb; i<utb; i++){
        //         printf("output[%d]: %d \n",i, output[i]);
        //     }
            
        // }
        if (tid == 0){
            printf("offset: \n");
            output[0] = input[0];
            printf("offset[%d]: %d \n",0, output[0]);
            for (int i=1; i<nthreads; i++){

                long int _ltb = nelem_p*(i-1); // lower bound for previous thread
                long int _utb = nelem_p*(i);   // upper bound for previous thread

                // output[_ltb]: offset[i-1]
                // output[_utb]: offset[i]
                output[_utb] = output[_ltb] + output[_utb-1] + input[_utb];
                printf("offset[%d]: %d \n",i, output[_utb]);
            }
              
        }
        #pragma omp barrier

        // Step 4: correct output by adding offsets for each thread
        for (int i = ltb+1; i < utb; i++) {
            output[i] += output[ltb];
        }
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
