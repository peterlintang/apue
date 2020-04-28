
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <name> \n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	if (argc != 2)
		usage(argv[0]);

	ret = shm_unlink(argv[1]);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to unlink: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	return 0;
}






