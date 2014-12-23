/*
 * test a given machine's host byte order
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	union {
		short	s;
		char	c[sizeof(short)];
	} un;

	un.s = 0x0102;

	printf("%s: ", "byte order");
	if (sizeof(short) == 2) {
		if (un.c[0] == 0x01 && un.c[1] == 0x02)
			printf("big endian\n");
		else if (un.c[0] == 0x02 && un.c[1] == 0x01)
			printf("little endian\n");
		else
			printf("unknow endian\n");
	}
	else {
		printf("sizeof(short) = %d\n", sizeof(short));
	}

	printf("host: %x\tnet: %x\n", 12345, htons(12345));
	return 0;
}
