
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
	int nsems;
	int i;
	unsigned short *ptr = NULL;

	/*
	struct ipc_perm {
		key_t __key;
		uid_t uid;
		gid_t gid;
		uid_t cuid;
		gid_t cgid;
		unsigned short mode;
		unsigned short __seq;
	};
	struct semid_ds {
		struct ipc_perm sem_perm;
		time_t sem_otime;
		time_t sem_ctime;
		unsigned long sem_nsems;
	};
	*/

	struct semid_ds info;
	union semun {
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *__buf;
	} arg;

	if (argc != 2)
		usage(argv[0]);

	semid = semget(ftok(argv[1], 0), 0, O_RDONLY);
	if (semid == -1)
	{
		fprintf(stderr, "%s failed to get sem: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	memset(&arg, 0, sizeof(arg));
	arg.buf = &info;
	ret = semctl(semid, 0, IPC_STAT, arg);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to get stat: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	nsems = arg.buf->sem_nsems;

	ptr = calloc(nsems, sizeof(unsigned short));
	if (ptr == NULL)
	{
		fprintf(stderr, "calloc %d x %ld mem failed\n", nsems, sizeof(unsigned short));
		exit(3);
	}
	arg.array = ptr;

	semctl(semid, 0, GETALL, arg);

	for (i = 0; i < nsems; i++)
	{
		fprintf(stdout, "index: %d, value: %d\n", i, arg.array[i]);
	}

	return ret;
}
