
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
	fprintf(stdout, "usage: %s [-e] <pathname> <nsems>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int c = 0;
	int oflag = 0;
	int nsems = 0;
	int semid = 0;

	oflag = IPC_CREAT | S_IRUSR | S_IWUSR;

	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}

	if (argc - 2 != optind)
		usage(argv[0]);

	nsems = atoi(argv[optind + 1]);
	semid = semget(ftok(argv[optind], 0), nsems, oflag);
	if (semid == -1)
	{
		fprintf(stderr, "%s failed to get sem: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	return ret;
}
