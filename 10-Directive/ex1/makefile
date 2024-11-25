help:
	@echo 'test'

compile:
	gcc -fopenacc helloworld.c -o helloworld

clean:
	rm -f single
	rm -f funnel
	rm -f serial
	rm -f multiple

run:
	@echo 'Current OMP_NUM_THREADS=${OMP_NUM_THREADS}'
	./helloworld
