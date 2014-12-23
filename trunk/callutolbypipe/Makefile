
SRCS=calutolbypipe.c 
OBJS=calutolbypipe.o 
TARGET=calutolbypipe

all:${TARGET}
${TARGET} : ${OBJS} err.o
	gcc -I../include -o ${TARGET} ${OBJS} err.o

${OBJS}:${SRCS} 
	gcc -I../include -c $< 
err.o: ../src/err.c
	gcc -I../include -c ../src/err.c

clean:	
	rm -f ${OBJS} ${TARGET} err.o
.PHONY: ${TARGET} ${OBJS} err.o clean
