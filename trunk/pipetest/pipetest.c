
/*
 * create a pipe and write 
 * to it , then read from it
 * and print the stdout
 */

#include "apue.h"

int main(int argc, char *argv[])
{
	char	buf[14];
	int 	fd[2];

	if (pipe(fd) < 0) {
		perror("pipe");
		exit(-1);
	}

	if (write(fd[1], "hello world", 12) < 0)
		perror("write");

	if (read(fd[0], buf, 12) < 0)
		perror("read");

	fprintf(stdout, "string: %s\n", buf);
	return 0;
}
