help:
	@echo 'test'

hybrid:
	mpicc -fopenmp hybrid.c -o hybrid

mpionly:
	mpicc mpionly.c -o mpionly

clean:
	rm -f hybrid
	rm -f mpionly
