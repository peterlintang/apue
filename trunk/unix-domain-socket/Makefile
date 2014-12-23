
all:
	gcc -o ud-server ud-server-test.c udsock-client.c udsock-server.c -I./
	gcc -o ud-client ud-client-test.c udsock-client.c udsock-server.c -I./
targets:
	gcc -c udsock-client.c -I./
	gcc -c udsock-server.c -I./
clean:
	rm -rf udsock-client.o
	rm -rf udsock-server.o
	rm -rf ud-server
	rm -rf ud-client
