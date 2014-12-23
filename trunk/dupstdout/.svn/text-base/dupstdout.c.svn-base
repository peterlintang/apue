

/*
 *
 * dup a file descriptor and 
 * write something ourt from
 * the new file descriptor
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;

//	if ((fd = dup(1)) == -1) {
//	if ((fd = dup2(1, 1023)) == -1) {
	if ((fd = fcntl(1, F_DUPFD, 1023)) == -1) {
		fprintf(stdout, "dup failed\n");
		perror("dup");
		exit(-1);
	} else {
		fprintf(stdout, "dup success %d\n", fd);
	}

	write(fd, "hello world\n", 40);

	return 0;

}
