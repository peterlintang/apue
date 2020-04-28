
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <shmname> <semname> <#loops>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int i;
	int fd = -1;
	int nloops = 0;
	int c;
	int *ptr = NULL;
	sem_t *sem = NULL;

	if (argc != 4)
	{
		usage(argv[0]);
	}

	nloops = atoi(argv[3]);

	fd = shm_open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to open: %s\n", argv[0], strerror(errno));
		exit(1);
	}

	ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == NULL)
	{
		fprintf(stderr, "%s failed to map size: %d, %s\n", argv[1], (int)sizeof(int), strerror(errno));
		shm_unlink(argv[1]);
		exit(1);
	}

	close(fd);

	sem = sem_open(argv[2], 0);
	if (SEM_FAILED == sem)
	{
		fprintf(stderr, "%s failed to open: %s\n", argv[2], strerror(errno));
		shm_unlink(argv[1]);
		exit(1);
	}

	for (i = 0; i < nloops; i++)
	{
		sem_wait(sem);
		fprintf(stdout, "pid: %ld, value: %d\n", (long)getpid(), (*ptr)++);
		sem_post(sem);
	}

	sem_close(sem);

	return 0;
}






