/*
 *
 * test the functions which change address from network bin to ascii
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	fprintf(stdout, "ascii: %s\tnetwork bin: %x\n", "192.168.253.119", inet_addr("192.168.253.119"));
	return 0;
}
