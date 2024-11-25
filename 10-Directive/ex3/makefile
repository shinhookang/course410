help:
	@echo 'make compile'
	@echo 'make run'

TARGET=kern2
compile:
	#gcc -c timer.c -o timer.o
	#gcc -c kern2.c -o kern2.o
	#gcc kern2.o timer.o -o kern2
	
	gcc -fopenmp -fopt-info-omp kern2.c timer.c -o ${TARGET}
	gcc -fopenmp -fopt-info-omp kern2_par.c timer.c -o ${TARGET}_par
	gcc -fopenmp -fopt-info-omp kern2_par_data.c timer.c -o ${TARGET}_par_data
	gcc -fopenmp -fopt-info-omp kern2_par_malloc.c timer.c -o ${TARGET}_par_malloc
	gcc kern2_serial.c timer.c -o ${TARGET}_serial

clean:
	rm -f ${TARGET}
	rm -f ${TARGET}_par 
	rm -f ${TARGET}_par_data
	rm -f ${TARGET}_par_malloc
	rm -f ${TARGET}_serial
	rm -f timer.o

run:
	./${TARGET}
	./${TARGET}_par
	./${TARGET}_par_data
	./${TARGET}_par_malloc
	./${TARGET}_serial
