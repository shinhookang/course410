help:
	@echo 'make compile'
	@echo 'make run'

TARGET=kern1
compile:
	#gcc -c timer.c -o timer.o
	#gcc -c kern1.c -o kern1.o
	#gcc kern1.o timer.o -o kern1
	
	gcc -fopenacc -fopt-info-optimized-omp kern1.c timer.c -o ${TARGET}
	gcc -fopenacc -fopt-info-optimized-omp kern1_par.c timer.c -o ${TARGET}_par
	gcc kern1_serial.c timer.c -o ${TARGET}_serial

clean:
	rm -f ${TARGET}
	rm -f ${TARGET}_par 
	rm -f ${TARGET}_serial
	rm -f timer.o

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	./${TARGET}
	./${TARGET}_par
	./${TARGET}_serial
