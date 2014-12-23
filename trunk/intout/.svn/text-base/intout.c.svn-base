#include "apue.h"
#include <fcntl.h>
#include <errno.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

char buf[500000];

int
main(int argc, char *argv[])
{
	int	ntowrite, nwrite;
	char 	*ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

//	set_fl(STDOUT_FILENO, O_NONBLOCK);

	ptr = buf;
	while (ntowrite > 0) 
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite= %d, errno = %d\n", nwrite, errno);

		if (nwrite > 0)
		{
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
//	clr_fl(STDOUT_FILENO, O_NONBLOCK);

	exit(0);
}
