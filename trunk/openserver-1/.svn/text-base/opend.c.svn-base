#include "opend.h"

char 	errmsg[MAXLINE];
int	oflag;
char	*pathname;

int
main(int argc, char *argv[])
{
	int	nread;
	char	buf[MAXLINE];

	for ( ; ; )
	{
		fprintf(stdout, "in opend\n");
		if ((nread = read(STDIN_FILENO, buf, MAXLINE)) < 0)
			err_sys("read error");
		else if (nread == 0)
			break;
		fprintf(stdout, "arguments: %s\n", buf); ///////////////
		request(buf, nread, STDOUT_FILENO);
	}
	exit(0);
}
