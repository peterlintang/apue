
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s [-e] <name> <length>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int oflag = 0;
	int ret = 0;
	int fd = -1;
	int size = 0;
	int c;
	int *ptr = NULL;

	oflag = O_RDWR | O_CREAT;
	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				oflag |= O_EXCL;
				break;
		}
	}

	if (optind != argc - 2)
	{
		usage(argv[0]);
	}

	size = atoi(argv[optind + 1]);

	fd = shm_open(argv[optind], oflag, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to open: %s\n", argv[0], strerror(errno));
		exit(1);
	}

	ret = ftruncate(fd, size);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed to set size: %d, %s\n", argv[optind], size, strerror(errno));
		shm_unlink(argv[optind]);
		exit(1);
	}

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == NULL)
	{
		fprintf(stderr, "%s failed to map size: %d, %s\n", argv[optind], size, strerror(errno));
		shm_unlink(argv[optind]);
		exit(1);
	}

	return 0;
}






