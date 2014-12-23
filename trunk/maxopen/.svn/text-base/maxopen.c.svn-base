

/*
 *
 * open as many files as possible,
 * until error and return
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define 	OPEN_MODE 	S_IRUSR | S_IWUSR

int main(int argc, char *argv[])
{
	int fd;
	int i 	= 0;

	while (1) {
		if ((fd = open("b.txt", O_RDWR | O_CREAT, OPEN_MODE)) == -1) {
			fprintf(stdout, "error");
			perror("open");
//			strerror(errno);
//			fprintf(stdout, "\n");
			exit(-1);
		}
		i++;
		fprintf(stdout, "open success: %d (%d)\n", fd, i);
	}

	exit(0);
}
