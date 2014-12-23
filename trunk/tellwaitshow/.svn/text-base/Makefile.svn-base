

SRCS=tellwaitshow.c ../src/err.c ../src/tellwait.c
OBJS=tellwaitshow.o ../src/err.o ../src/tellwait.o
TARGETS=tellwaitshow notellshow

all: ${TARGETS}

tellwaitshow: tellwaitshow.c ../src/err.c ../src/tellwait.c
	gcc -I../include -o tellwaitshow ${SRCS}
notellshow: notellshow.c ../src/err.c
	gcc -I../include -o notellshow notellshow.c ../src/err.c
clean:
	rm -f ${TARGETS} ${OBJS}
.PHONY: ${TARGETS} ${OBJS} 
