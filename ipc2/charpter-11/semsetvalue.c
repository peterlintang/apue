
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
	fprintf(stdout, "usage: %s <pathname> [values...]\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int semid = 0;
	int nsems;
	int i;
	unsigned short *ptr = NULL;

	struct semid_ds info;
	union semun {
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *__buf;
	} arg;

	if (argc < 2)
		usage(argv[0]);

	semid = semget(ftok(argv[1], 0), 0, O_RDONLY);	// 使用O_WRONLY不行，但O_RDONLY却可以？？？
	if (semid == -1)
	{
		fprintf(stderr, "%s failed to get sem: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	memset(&info, 0, sizeof(info));
	memset(&arg, 0, sizeof(arg));
	arg.buf = &info;
	ret = semctl(semid, 0, IPC_STAT, arg);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to get stat: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	nsems = arg.buf->sem_nsems;

	if (argc != nsems + 2)
	{
		fprintf(stderr, "%d semaphores in set, %d values specified\n", nsems, argc - 2);
		exit(2);
	}

	ptr = calloc(nsems, sizeof(unsigned short));
	if (ptr == NULL)
	{
		fprintf(stderr, "calloc %d x %ld mem failed\n", nsems, sizeof(unsigned short));
		exit(3);
	}
	arg.array = ptr;

	for (i = 0; i < nsems; i++)
	{
		ptr[i] = atoi(argv[i + 2]);
	}

	semctl(semid, 0, SETALL, arg);

	return ret;
}
