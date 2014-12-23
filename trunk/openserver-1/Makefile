OPENDSRCS=opend.c request.c buf_args.c cli_args.c ../src/server.c ../src/err.c ../src/s_pipe.c
OPENDOBJS=opend.o request.o buf_args.o cli_args.o ../src/server.o ../src/err.o ../src/s_pipe.o
OPENCLIENTSRCS=open.c csopen.c ../src/server.c ../src/err.c ../src/s_pipe.c
OPENCLIENTOBJS=open.o csopen.o ../src/server.o ../src/err.o ../src/s_pipe.o
CFLAGS=../include


all:opend open

opend:${OPENDSRCS}
	gcc -g -I../include -o opend ${OPENDSRCS} 

open:${OPENCLIENTSRCS}
	gcc -g -I../include -o open ${OPENCLIENTSRCS} 

#${OPENDOBJS}:${OPENDSRCS}
#	gcc -g -I../include -c $< -o $@

#${OPENCLIENTOBJS}:${OPENCLIENTSRCS}
#	gcc -g -I../include -c $< -o $@

clean: 
	rm -f opend open 
	
.PHONY: all opend open clean
