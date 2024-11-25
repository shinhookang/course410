help:
	@echo 'test'

TARGET=kern1
compile:
	#gcc -fopenacc helloworld.c -o helloworld
	#gcc -c timer.c -o timer.o
	#gcc -c kern1.c -o kern1.o
	#gcc kern1.o timer.o -o kern1
	
	#gcc kern1.c timer.c -o ${TARGET}
	gcc kern1_serial.c timer.c -o ${TARGET}

clean:
	rm -f ${TARGET}
	rm -f kern1_serial
	rm -f timer.o

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	#./addvec
	#./axpy
	./${TARGET}
