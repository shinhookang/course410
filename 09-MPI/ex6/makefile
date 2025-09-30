help:
	@echo 'test'

compile: single funnel serial multiple

single:
	mpicc -fopenmp single.c -o single

funnel:
	mpicc -fopenmp funnel.c -o funnel
serial:
	mpicc -fopenmp serial.c -o serial
multiple:
	mpicc -fopenmp multiple.c -o multiple
clean:
	rm -f single
	rm -f funnel
	rm -f serial
	rm -f multiple

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	#mpirun -np 4 ./single
	#mpirun -np 4 ./funnel
	#mpirun -np 2 ./serial
	mpirun -np 2 ./multiple
