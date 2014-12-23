
SRCS=prtshmadd.c ../src/err.c
OBJS=prtshmadd.o ../src/err.o
TARGETS=prtshmadd

all: ${TARGETS}
	
prtshmadd:${OBJS}
	gcc -I../include -o prtshmadd ${SRCS}
clean:
	rm -f ${TARGETS} ${OBJS}
.PHONY: clean ${TARGETS} ${OBJS}
	
