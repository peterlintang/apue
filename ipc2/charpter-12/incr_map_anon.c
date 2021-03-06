
/*
 * 使用匿名映射
 */
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

struct shared {
	int count;
	sem_t sem;
};

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <#loops>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int i;
	int nloops = 0;

	struct shared share;
	struct shared *ptr = NULL;

	if (argc != 2)
		usage(argv[0]);

	nloops = atoi(argv[1]);

	ptr = mmap(NULL, sizeof(share), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON /*MAP_PRIVATE:父进程改动子进程看不见，子进程改动父进程看不见*/, -1, 0); // 匿名映射
	if (ptr == NULL)
	{
		fprintf(stderr, "%s mmap failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	ret = sem_init(&ptr->sem, 1, 1);
	if (0 != ret)
	{
		fprintf(stderr, "sem init failed: %s\n", strerror(errno));
		munmap(ptr, sizeof(share));
		exit(1);
	}


	setbuf(stdout, NULL);

	if (fork() == 0)
	{
		for (i = 0; i < nloops; i++)
		{
			sem_wait(&ptr->sem);
			fprintf(stdout, "child: %ld, %d\n", (long)getpid(), ptr->count++);
			sem_post(&ptr->sem);
		}
		exit(0);
	}

	for (i = 0; i < nloops; i++)
	{
		sem_wait(&ptr->sem);
		fprintf(stdout, "parent: %ld, %d\n", (long)getpid(), ptr->count++);
		sem_post(&ptr->sem);
	}

//	sem_destroy(&ptr->sem);
	return ret;
}
