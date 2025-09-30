help:
	@echo 'test'

compile: hybrid 

hybrid:
	mpicc -fopenmp hybrid-pi.c -o pi

clean:
	rm -f pi

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	mpirun -np 4 ./pi
