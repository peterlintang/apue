SRCS=bindunixaddr.c
OBJS=bindunixaddr.o
TARGETS=bindunixaddr

all: ${TARGETS}

bindunixaddr: bindunixaddr.c
	gcc -I../include -o bindunixaddr bindunixaddr.c ../src/err.c
clean:
	rm -f ${TARGETS} ${OBJS}
.PHONY:${TARGETS} ${OBJS}
