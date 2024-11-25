#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int main(int argc, char *argv[]){

  int nsize = 20000000, ntimes=16;
  double *a = malloc(nsize * sizeof(double));
  double *b = malloc(nsize * sizeof(double));
  double *c = malloc(nsize * sizeof(double));

  struct timespec tstart; 

  #pragma acc kernels
  for (int i=0; i<nsize; i++){
    a[i] = 1.0;
    b[i] = 2.0; 
  }
    
  double scalar = 3.0;

  double time_sum = 0.0;
  for (int itime=0; itime < ntimes; itime++)
  {
    cpu_timer_start(&tstart);

    #pragma acc kernels
    for (int i=0; i<nsize; i++){
      c[i] = a[i] + scalar * b[i]; 
    }

    time_sum += cpu_timer_stop(tstart); 
  }
  printf("Average runtime is %lf msecs\n", time_sum/ntimes);

  free(a);
  free(b);
  free(c);
  
  return(0); 

}
