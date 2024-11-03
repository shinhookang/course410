# OpenMP

Date: November 2nd, 2024

## Mac

Install required packages `brew install llvm libomp`

Modify `.zshrc` as follows: 
```bash
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
```

Compile programs using 
```bash 
clang -fopenmp ex1.c -o ex1
```


## Windows Subsystems for Linux

### Example 1: Hello World
Under `ex1` directory, compile `ex1.c`. 
Set `-fopenmp` option to enable *OpenMP*. 
```bash
export OMP_NUM_THREADS=4
gcc -fopenmp ex1.c -o ex1
gcc -fopenmp ex1-func.c -o ex1-func
gcc -fopenmp ex1-clause.c -o ex1-clause
gcc -fopenmp ex1-output-single.c -o ex1-output-single
gcc -fopenmp ex1-output-thread0.c -o ex1-output-thread0
```
Use `lscpu` command to check the number of cores. 

### Example 2: Race condition
```bash
export OMP_NUM_THREADS=4
gcc -fopenmp ex2.c -o ex2
gcc -fopenmp ex2-atomic.c -o ex2-atomic
gcc -fopenmp ex2-critical.c -o ex2-critical
gcc -fopenmp ex2-reduction.c -o ex2-reduction
```

### Example 3: Private and firstprivate clauses
```bash
export OMP_NUM_THREADS=4
gcc -fopenmp private.c -o private
gcc -fopenmp firstprivate.c -o firstprivate
```

### Example 4: Parallel For
```bash
export OMP_NUM_THREADS=4
gcc -fopenmp parfor.c -o parfor
gcc -fopenmp parfor-compact.c -o parfor-compact
gcc -fopenmp parfor-sum.c -o parfor-sum
gcc -fopenmp parfor-sum-reduction.c -o parfor-sum-reduction
```

[Reference](https://www.openmp.org/)
