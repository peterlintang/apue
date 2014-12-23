SRCS=getenv.c
OBJS=getenv.o
TARGETS=getenv

all: ${TARGETS}

getenv: getenv.c
	gcc -I../include -Wall -g -o getenv getenv.c

clean: 
	rm -f ${TARGETS} ${OBJS}
.PHONY: ${TARGETS} all clean
