SRCS=structtest.c
OBJS=structtest.o
TARGETS=structtest

all: ${TARGETS}

structtest:structtest.c
	gcc -I../include -o structtest structtest.c
clean:
	rm -rf ${TARGETS} ${OBJS}
.PHONY:${TARGETS} ${OBJS}
