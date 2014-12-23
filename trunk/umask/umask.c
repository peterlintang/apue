
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	mode_t		old;
	int		fd;
	int		dirfd;

	old = umask(S_IROTH | S_IWOTH | S_IXOTH);
//	old = umask(0);

	/* open current work dir  */
	if ((dirfd = open("./", O_RDONLY)) == -1) {
		perror("open ./");
		exit(-1);
	} else {
		fprintf(stdout, "open ./: %d\n", dirfd);
	}
		


	if ((fd = open("hello.txt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP)) == -1) {
		perror("open");
		exit(-1);
	}

	return 0;
}
