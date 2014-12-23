SRCS=ruptime.c ruptimed.c
OBJS=ruptime.o ruptimed.o
TARGETS=ruptime ruptimed

all: ${TARGETS}

ruptime:ruptime.c
	gcc -g -I../include -o ruptime ruptime.c ../src/err.c ../src/connect_retry.c
ruptimed:ruptimed.c
	gcc -g -I../include -o ruptimed ruptimed.c ../src/err.c ../src/daemonize.c ../src/initserver.c
clean: 
	rm -rf ruptime ruptimed
#	rm -f ${TARGETS) ${OBJS}
.PHONY:all ${TARGETS} clean
