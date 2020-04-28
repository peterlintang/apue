
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <pathname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int ret = 0;

	if (argc != 2)
		usage(argv[0]);

	fd = shmget(ftok(argv[1], 0), 0, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to get: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	ret = shmctl(fd, IPC_RMID, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "%s failed to ctl: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	return 0;
}






