# OpenMP

Date: October 28th, 2024

## Windows Subsystems for Linux

### Example 1: Hello World
Under `ex1` directory, compile `helloworld.c`. 
Set `-fopenmp` option to enable *OpenMP*. 
```bash
export OMP_NUM_THREADS=4
gcc -fopenmp helloworld.c -o helloworld
```
Use `lscpu` command to check the number of cores. 

[Reference](https://www.openmp.org/)
