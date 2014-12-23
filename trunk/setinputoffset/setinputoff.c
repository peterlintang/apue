#include <fcntl.h>
#include "apue.h" 

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...) 
#endif

#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define BUFSIZE 1024

int 
main(int argc, char *argv[])
{
	int fd;
	char *buf = malloc(sizeof(char ) * 1024);
	char tmp[1024];

	memset(tmp, 0, sizeof(char) * 1024);

	if (buf == NULL)
	{
		errprintf("malloc error!\n");
		exit(1);
	}

	/*test open write lseek read and close sys call*/
	if ((fd = open("./hello.txt", O_RDWR |  O_CREAT, FILE_MODE)) == -1)
		errprintf("can't open!\n");
	
	sprintf(buf, "hello world");
	
	if (write(fd, buf, strlen(buf)) == -1)
		errprintf("can't write!\n");

	lseek(fd, 0, SEEK_SET);
	
	if (read(fd, tmp, strlen(buf)) == -1)
		errprintf("can't read!\n");

	dprintf("read from file: %s\n", tmp);
	
	close(fd);
		
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
	{
		errprintf("can't seek!\n");
//		exit(1);
	}
	else
		dprintf("seek ok!\n");

	/*test io effeciency*/
/*	int n;
	char buff[BUFSIZE];

	while ((n = read(STDIN_FILENO, buff, BUFSIZE)) > 0)
	{
		if (write(STDOUT_FILENO, buff, n) != n)
		{
			errprintf("write error\n");
		}
	}
	
	if (n < 0)
		errprintf("read error\n");
*/
	/*dup a file descripter*/
	int k;
	int newfd = dup(1);
	dprintf("new fd: %d\n", newfd);
	if ((k = write(newfd, "hello world\n", strlen("hello world\n"))) < 0)
		dprintf("write error\n");
	else
		dprintf("write %d bytes\n", k);

	exit(0);
}


