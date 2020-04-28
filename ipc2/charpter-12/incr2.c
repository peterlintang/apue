
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/mman.h>

#include <errno.h>
#include <unistd.h>

#define SEM_NAME	"/mysem"

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <pathname> <#loops>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int i;
	int fd = -1;
	int nloops = 0;
	int zero = 0;
	int *ptr = NULL;
	sem_t *sem = NULL;

	if (argc != 3)
		usage(argv[0]);

	nloops = atoi(argv[2]);

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s open failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	if ((ret = write(fd, &zero, sizeof(int))) != sizeof(int))
	{
		fprintf(stderr, "%s write failed: %s\n", argv[1], strerror(errno));
		close(fd);
		exit(1);
	}

	ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED /*MAP_PRIVATE:父进程改动子进程看不见，子进程改动父进程看不见*/, fd, 0);
	if (ptr == NULL)
	{
		fprintf(stderr, "%s mmap failed: %s\n", argv[1], strerror(errno));
		close(fd);
		exit(1);
	}

	close(fd);

	sem = sem_open(SEM_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (SEM_FAILED == sem)
	{
		fprintf(stderr, "%s open failed: %s\n", SEM_NAME, strerror(errno));
		munmap(ptr, sizeof(int));
		exit(1);
	}

	sem_unlink(SEM_NAME);

	setbuf(stdout, NULL);

	if (fork() == 0)
	{
		for (i = 0; i < nloops; i++)
		{
			sem_wait(sem);
			fprintf(stdout, "child: %ld, %d\n", (long)getpid(), (*ptr)++);
			sem_post(sem);
		}
		exit(0);
	}

	for (i = 0; i < nloops; i++)
	{
		sem_wait(sem);
		fprintf(stdout, "parent: %ld, %d\n", (long)getpid(), (*ptr)++);
		sem_post(sem);
	}

	return ret;
}
