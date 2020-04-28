
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
	sem_t *sem = NULL;
	unsigned int value = 0;

	if (2 != argc)
	{
		usage(argv[0]);
	}

	sem = sem_open(argv[1], O_RDWR);
	if (SEM_FAILED == sem)
	{
		fprintf(stderr, "%s sem_open failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	sem_post(sem);

	sem_close(sem);

	return 0;
}




