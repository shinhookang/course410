#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "timer.h"

int main(int argc, char *argv[]){

  int nsize = 20000000, ntimes=16;
  double* restrict a = acc_malloc(nsize * sizeof(double));
  double* restrict b = acc_malloc(nsize * sizeof(double));
  double* restrict c = acc_malloc(nsize * sizeof(double));

  struct timespec tstart; 

  #pragma acc parallel loop deviceptr(a, b)
  for (int i=0; i<nsize; i++){
    a[i] = 1.0;
    b[i] = 2.0; 
  }
    
  double scalar = 3.0;

  double time_sum = 0.0;
  for (int itime=0; itime < ntimes; itime++)
  {
    cpu_timer_start(&tstart);

    #pragma acc parallel loop deviceptr(a, b, c)
    for (int i=0; i<nsize; i++){
      c[i] = a[i] + scalar * b[i]; 
    }

    time_sum += cpu_timer_stop(tstart); 
  }
  printf("Average runtime is %lf msecs\n", time_sum/ntimes);

  acc_free(a);
  acc_free(b);
  acc_free(c);
  
  return(0); 

}
