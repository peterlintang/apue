
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
	fprintf(stdout, "usage: %s [-n] [-u] [-c] <pathname> operation...\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int semid = 0;
	int i;
	int c;
	int flag = 0;
	int nops;
	int convert = 0;
	struct sembuf *ptr = NULL;

	while ((c = getopt(argc, argv, "nuc")) != -1)
	{
		switch (c)
		{
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 'u':
				flag |= SEM_UNDO;
				break;
			case 'c':
				convert = 1;
				break;
		}
	}

	if (argc - optind < 2)
		usage(argv[0]);

	semid = semget(ftok(argv[optind], 0), 0, O_RDONLY);
	if (semid == -1)
	{
		fprintf(stderr, "%s failed to get sem: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	optind++;
	nops = argc - optind;

	ptr = calloc(nops, sizeof(struct sembuf));
	if (ptr == NULL)
	{
		fprintf(stderr, "calloc %d x %ld mem failed\n", nops, sizeof(struct sembuf));
		exit(3);
	}

	for (i = 0; i < nops; i++)
	{
		ptr[i].sem_num = i;
		ptr[i].sem_op = atoi(argv[optind + i]);
		if (convert)
			ptr[i].sem_op = 0 - ptr[i].sem_op;
		ptr[i].sem_flg = flag;
	}

	ret = semop(semid, ptr, nops);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to op: %s\n", argv[optind - 1], strerror(errno));
		exit(1);
	}

	return ret;
}
