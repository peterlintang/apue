
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
	fprintf(stdout, "usage: %s [-e] [-i value] name\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	sem_t *sem = NULL;
	int c = 0;
	int flags = 0;
	unsigned int value = 0;

	flags = O_RDWR | O_CREAT;
	value = 1;

	while ((c = getopt(argc, argv, "ei:")) != -1)
	{
		switch (c) 
		{
		case 'e':
			flags |= O_EXCL;
			break;
		case 'i':
			value = atoi(optarg);
			break;
		}
	}

	if (argc - 1 != optind)
	{
		usage(argv[0]);
	}

	sem = sem_open(argv[optind], flags, S_IRUSR | S_IWUSR, value);
	if (SEM_FAILED == sem)
	{
		fprintf(stderr, "%s sem_open failed: %s\n", argv[optind], strerror(errno));
		exit(1);
	}
	
	sem_close(sem);

	return 0;
}




