
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define WDTDEV		"/dev/mywdt"
#define WDTOPENMODE	O_RDWR

int main(int argc, char *argv[])
{
	int fd;
	int count = 0;
	
	if ((fd = open(WDTDEV, WDTOPENMODE)) < 0) {
		fprintf(stderr, "open %s: fail\n", WDTDEV);
		exit(-1);
	}

	while (1) {
		fprintf(stdout, "write to %s (%d)\n", WDTDEV, ++count);
		if (write(fd, "\0",1) < 0) {
			fprintf(stderr, "write error\n");
			exit(-1);
		}
		sleep(5);
	}
	close(fd);
	exit(0);
}
