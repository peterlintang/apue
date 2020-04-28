
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <errno.h>
#include <unistd.h>

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <pathname> \n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int semid = 0;


	if (argc != 2)
		usage(argv[0]);

	semid = semget(ftok(argv[1], 0), 0, 0);
	if (semid == -1)
	{
		fprintf(stderr, "%s failed to get sem: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	ret = semctl(semid, 0, IPC_RMID);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to remove sem: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	return ret;
}
