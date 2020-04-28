
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
	fprintf(stdout, "usage: %s <shmname> <#loops> <#usec>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd = -1;
	int nloops = 0;
	int usecs = 0;
	int i;
	char msg[MESGSIZE];
	struct shmstruct *ptr = NULL;

	if (argc != 4)
	{
		usage(argv[0]);
	}

	nloops = atoi(argv[2]);
	usecs = atoi(argv[3]);

	fd = shm_open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to open: %s\n", argv[0], strerror(errno));
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


	for (i = 0; i < nloops; i++)
	{
		usleep(usecs);

		/* my flow
		sem_wait(&ptr->nempty);
		sem_wait(&ptr->mutex);

		snprintf(msg, MESGSIZE, "pid: %ld, mesg: %d\n", (long)getpid(), i);
		strcpy(&ptr->msgdata[ptr->msgoff[ptr->input]], msg);
		ptr->input++;
		if (ptr->input>= NMESG)
			ptr->input= 0;

		sem_post(&ptr->mutex);
		sem_post(&ptr->nstored);
		*/

		snprintf(msg, MESGSIZE, "pid: %ld, mesg: %d\n", (long)getpid(), i);

		if (sem_trywait(&ptr->nempty) == -1)
		{
//			fprintf(stdout, "pid: %ld overflow: %s(%s)\n", (long)getpid(), strerror(errno), strerror(EAGAIN));
			if (errno == EAGAIN)
			{
//				fprintf(stdout, "pid: %ld overflow\n", (long)getpid());
				sem_wait(&ptr->noverflowmutex);
				ptr->noverflow++;
				sem_post(&ptr->noverflowmutex);
				continue;
			}
			else
			{
				fprintf(stderr, "sem_trywati error\n");
			}
		}

		sem_wait(&ptr->mutex);
		strcpy(&ptr->msgdata[ptr->msgoff[ptr->input]], msg);
		ptr->input++;
		if (ptr->input>= NMESG)
			ptr->input= 0;
		sem_post(&ptr->mutex);

		sem_post(&ptr->nstored);
	}

	return 0;
}






