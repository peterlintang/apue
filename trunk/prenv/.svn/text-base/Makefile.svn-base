#include ./test.d

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, $(wildcard *.c))

all: prenv.o

	@echo $(SRC)
	@echo $(OBJ)
	gcc -Wall -o prenv prenv.o

prenv.o:
	gcc -Wall -c prenv.c
prenv.d:prenv.c
	gcc -M $<> $@.$$$$; \
	sed 's,\($*\).o[:]*,\1.o $@:,g' <$@.$$$$> $@;\
	#rm -f $@.$$$$
clean:
	rm -f prenv.o prenv
.PHONY: all
.PHONY: prenv
.PHONY: clean
