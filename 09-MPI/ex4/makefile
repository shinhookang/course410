help:
	@echo 'test'

compile: hybrid mpionly

hybrid:
	mpicc -fopenmp hybrid.c -o hybrid

mpionly:
	mpicc mpionly.c -o mpionly

clean:
	rm -f hybrid
	rm -f mpionly

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	mpirun -np 4 ./hybrid
	mpirun -np 4 ./mpionly
