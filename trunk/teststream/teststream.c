#include "apue.h"
#include <fcntl.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


int
main(int argc, char *argv[])
{
	int 	i, fd;

	for (i = 1; i < argc; i++)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
		{
			err_ret("%s: can't open", argv[i]);
			continue;
		}

		if (isastream(fd) == 0)
		{
			err_ret("%s: not a stream", argv[i]);
		}
		else
		{
			err_msg("%s: stream device",argv[i]);
		}
	}
	exit(0);

}
