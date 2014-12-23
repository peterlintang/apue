
SRCS=getaddrinfo.c
OBJS=getaddrinfo.o
TARGETS=getaddrinfo

all: ${TARGETS}

getaddrinfo: getaddrinfo.c
	gcc -I../include -o getaddrinfo getaddrinfo.c ../src/err.c
clean:
	rm -f ${TARGETS} ${OBJS}
.PHONY:all ${TARGETS} clean

