
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
	fprintf(stdout, "usage: %s <pathname> <#offset> <#length> <#value>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int ret = 0;
	int i;
	int length = 0;
	int offset = 0;
	int value = 0;
	char *name = NULL;
	char *ptr = NULL;
	struct shmid_ds buf;

	if (argc != 5)
		usage(argv[0]);

	name = argv[1];
	offset = atoi(argv[2]);
	length = atoi(argv[3]);
	value = atoi(argv[4]);

	fd = shmget(ftok(name, 0), 0, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to get: %s\n", name, strerror(errno));
		exit(1);
	}

	ptr = shmat(fd, NULL, 0);
	if (ptr == (char *)-1)
	{
		fprintf(stderr, "%s failed to at: %s\n", name, strerror(errno));
		exit(1);
	}

	memset(&buf, 0, sizeof(buf));
	ret = shmctl(fd, IPC_STAT, &buf);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to ctl: %s\n", name, strerror(errno));
		exit(1);
	}
	
	if (buf.shm_segsz < offset || buf.shm_segsz < offset + length)
	{
		fprintf(stderr, "%s size: %d, offset: %d,length: %d\n", name, (int)buf.shm_segsz, offset, length);
		exit(1);
	}

	for (i = 0; i < length; i++)
	{
		ptr[offset + i] = value;
	}

	shmdt(ptr);

	return 0;
}






