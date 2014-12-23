
SRCS=add2.c copram.c
OBJS=add2.o copram.o
TARGETS=add2 copram

all: ${TARGETS}

add2:add2.c
	gcc -I../include -o add2 add2.c ../src/err.c

copram:copram.c
	gcc -I../include -o copram copram.c ../src/err.c
clean:
	rm -f ${TARGETS} ${OBJS}

.PHONY: ${TARGETS} ${OBJS} clean
