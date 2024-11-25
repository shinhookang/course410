help:
	@echo 'make compile'
	@echo 'make run'

TARGET=kern2
compile:
	#gcc -c timer.c -o timer.o
	#gcc -c kern2.c -o kern2.o
	#gcc kern2.o timer.o -o kern2
	
	gcc -fopenmp -fopt-info-omp kern2.c timer.c -o ${TARGET}
	gcc -fopenmp -fopt-info-omp kern2_map.c timer.c -o ${TARGET}_map
	gcc -fopenmp -fopt-info-omp kern2_data.c timer.c -o ${TARGET}_data
	#gcc -fopenmp -fopt-info-omp kern2_par_malloc.c timer.c -o ${TARGET}_par_malloc
	gcc kern2_serial.c timer.c -o ${TARGET}_serial

clean:
	rm -f ${TARGET}
	rm -f ${TARGET}_map
	rm -f ${TARGET}_data
	rm -f ${TARGET}_par_malloc
	rm -f ${TARGET}_serial
	rm -f timer.o

run:
	./${TARGET}
	./${TARGET}_map
	./${TARGET}_data
	#./${TARGET}_par_malloc
	./${TARGET}_serial
