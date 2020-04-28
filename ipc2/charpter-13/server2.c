
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

#define NMESG		16
#define MESGSIZE	256

struct shmstruct {
	sem_t mutex;
	sem_t nempty;
	sem_t nstored;
	int input;
	long noverflow;
	sem_t noverflowmutex;
	long msgoff[NMESG];
	char msgdata[NMESG * MESGSIZE];
};

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <shmname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd = -1;
	int i;
	struct shmstruct *ptr = NULL;
	long nlastoverflow = 0;
	long tmp = 0;

	if (argc != 2)
	{
		usage(argv[0]);
	}


	fd = shm_open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to open: %s\n", argv[0], strerror(errno));
		exit(1);
	}

	ret = ftruncate(fd, sizeof(struct shmstruct));
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to set size: %d, %s\n", argv[1], (int)sizeof(struct shmstruct), strerror(errno));
		shm_unlink(argv[1]);
		exit(1);
	}

	ptr = mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == NULL)
	{
		fprintf(stderr, "%s failed to map size: %d, %s\n", argv[1], (int)sizeof(struct shmstruct), strerror(errno));
		shm_unlink(argv[1]);
		exit(1);
	}

	close(fd);

	for (i = 0; i < NMESG; i++)
	{
		ptr->msgoff[i] = i * MESGSIZE;
	}
	sem_init(&ptr->mutex, 1, 1);
	sem_init(&ptr->nempty, 1, NMESG);
	sem_init(&ptr->nstored, 1, 0);
	sem_init(&ptr->noverflowmutex, 1, 1);


	i = 0;
	nlastoverflow = 0;

	for ( ; ; )
	{
		sem_wait(&ptr->nstored);
		sem_wait(&ptr->mutex);
//		fprintf(stdout, "index = %d: %s\n", i, &ptr->msgdata[ptr->msgoff[i]]);
		if (++i >= NMESG)
			i = 0;
		sem_post(&ptr->mutex);
		sem_post(&ptr->nempty);

		sem_wait(&ptr->noverflowmutex);
		tmp = ptr->noverflow;
		sem_post(&ptr->noverflowmutex);
//		fprintf(stdout, "tmp: %ld, nlastoverflow: %ld\n", tmp, nlastoverflow);
		if (tmp != nlastoverflow)
		{
			fprintf(stdout, "noverflow = %ld\n", tmp);
			nlastoverflow = tmp;
		}
	}

	return 0;
}






