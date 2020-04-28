
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
	fprintf(stdout, "usage: %s [-e] <pathname> <#length>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int length = 0;
	int c;
	int oflag;
	char *ptr = NULL;

	oflag = S_IRUSR | S_IWUSR | IPC_CREAT;
	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}

	if (argc != optind + 2)
		usage(argv[0]);

	length = atoi(argv[optind + 1]);
	fd = shmget(ftok(argv[optind], 0), length, oflag);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to get: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	ptr = shmat(fd, NULL, 0);
	if (ptr == (char *)-1)
	{
		fprintf(stderr, "%s failed to at: %s\n", argv[optind], strerror(errno));
		exit(1);
	}

	return 0;
}






