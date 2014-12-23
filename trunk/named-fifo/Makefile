

all:
	gcc -o test test-named-fifo.c named-fifo.c -I./
	gcc -o test-2 test-named-fifo2.c named-fifo.c -I./
target:
	gcc -c named-fifo.c -I./

clean:
	rm -rf named-fifo.o
	rm -rf test
	rm -rf test-2
