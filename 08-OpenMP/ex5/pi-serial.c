#include <stdio.h>
#include <omp.h>
#include <math.h>

#define NUM_STEPS 1000000000

// arctan(1) = pi/4
// arctan(1) = integral of 1/(1+x*x) from 0 to 1
// pi can be approximated using the Riemann sum approach 
// by integrating the function 1/(1+x*x) over the interval [0,1]


int main() {
    double pi, sum = 0.0;
    double dx = 1.0 / (double) NUM_STEPS;
    
    double start_time = omp_get_wtime();
   
    for (int i = 0; i < NUM_STEPS; i++)
    {
	    double x = i * dx;
	    sum += 1.0 / (1.0 + x*x);
    }
	
    pi = sum * dx * 4.0; 
    
    double end_time = omp_get_wtime();
    double run_time = end_time - start_time;
    
    printf("Pi true value   : %.15f\n", M_PI);
    printf("Pi approximation: %.15f\n", pi);
    printf("Difference: %.15g\n", pi-M_PI);
    printf("Time taken: %.4f seconds\n", run_time);
    
    return 0;
}
