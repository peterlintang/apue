

/*
 *
 * create a file and write hello world\n into 
 * the file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OPEN_MODE 	S_IRUSR | S_IWUSR
#define FILE_NAME	"hello.txt"

int main(int argc, char *argv[])
{
	int fd;

//	if ((fd = creat(FILE_NAME, OPEN_MODE)) == -1) {
	if ((fd = open(FILE_NAME, O_RDWR | O_CREAT | O_EXCL, OPEN_MODE)) == -1) {
		perror("creat");
		exit(-1);
	} else {
		fprintf(stdout, "creat file %s success\n", FILE_NAME);
//		exit(0);
	}

	if (write(fd, "hello world\n", 12) < 0) {
		perror("write");
		exit(-1);
	}


	if (close(fd) == -1) {
		perror("close");
		exit(-1);
	}

	return 0;

}
