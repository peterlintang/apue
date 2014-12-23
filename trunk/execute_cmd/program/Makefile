

SRCS=../src/server.c ../src/client.c ../src/server_addr.c ../src/client_addr.c
CFLAGS=-D_GNU_SOURCE

all:
	gcc -o execute_server ${CFLAGS} execute_server.c ${SRCS} -I../include
	gcc -o execute_client ${CFLAGS} execute_client.c ${SRCS} -I../include
	gcc -o execute_cmd    ${CFLAGS} execute_cmd.c    ${SRCS} -I../include
	gcc -o new_server     ${CFLAGS} new_server.c     ${SRCS} -I../include

clean:
	rm -rf execute_server execute_client execute_cmd new_server
