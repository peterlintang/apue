#include "apue.h"
#include <fcntl.h>
#include <utime.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, args)



int
main(int argc, char *argv[])
{
	int 		i, fd;
	struct stat 	statbuf;
	struct utimbuf 	timebuf;

	for (i = 1; i < argc; i++)
	{
		if (stat(argv[i], &statbuf) < 0)
		{
			errprintf("stat file: %s error\n", argv[i]);
			continue;
		}
		
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
		{
			errprintf("open file: %s error\n", argv[i]);
			continue;
		}

		close(fd);

		timebuf.actime  = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		if (utime(argv[i], &timebuf) < 0)
		{
			errprintf("utime file: %s error\n", argv[i]);
			continue;
		}
	}

	exit(0);
}
