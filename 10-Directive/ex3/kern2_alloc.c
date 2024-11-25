#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "timer.h"

int main(int argc, char *argv[]){

  int nsize = 20000000, ntimes=16;
  double* a = omp_target_alloc(nsize * sizeof(double),omp_get_default_device());
  double* b = omp_target_alloc(nsize * sizeof(double),omp_get_default_device());
  double* c = omp_target_alloc(nsize * sizeof(double),omp_get_default_device());

  struct timespec tstart; 

  #pragma omp target teams distribute parallel for simd is_device_ptr(a,b,c)
  for (int i=0; i<nsize; i++){
    a[i] = 1.0;
    b[i] = 2.0; 
  }
    
  double scalar = 3.0;

  double time_sum = 0.0;
  for (int itime=0; itime < ntimes; itime++)
  {
    cpu_timer_start(&tstart);

    #pragma omp target teams distribute parallel for simd is_device_ptr(a,b,c)
    for (int i=0; i<nsize; i++){
      c[i] = a[i] + scalar * b[i]; 
    }

    time_sum += cpu_timer_stop(tstart); 
  }
  printf("Average runtime is %lf msecs\n", time_sum/ntimes);

  omp_target__free(a,omp_get_default_device());
  omp_target__free(b,omp_get_default_device());
  omp_target__free(c,omp_get_default_device());
  
  return(0); 

}
