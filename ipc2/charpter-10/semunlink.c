
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s name\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	if (argc != 2)
		usage(argv[0]);

	ret = sem_unlink(argv[1]);
	if (-1 == ret)
	{
		fprintf(stderr, "%s sem_unlink failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	return 0;
}




