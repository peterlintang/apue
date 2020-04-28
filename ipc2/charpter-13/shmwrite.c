
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
	fprintf(stdout, "usage: %s <name> <offset> <length> <value>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd = -1;
	char *ptr = NULL;
	struct stat buf;
	int i;

	char *name = NULL;
	int length = 0;
	int offset = 0;
	int value = 0;

	if (argc != 5)
		usage(argv[0]);

	name = argv[1];
	offset = atoi(argv[2]);
	length = atoi(argv[3]);
	value = atoi(argv[4]);


	fd = shm_open(name, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		fprintf(stderr, "%s failed to open: %s\n", name, strerror(errno));
		exit(1);
	}

	memset(&buf, 0, sizeof(buf));
	ret = fstat(fd, &buf);
	if (ret == -1)
	{
		fprintf(stderr, "%s failed get stat: %s\n", name, strerror(errno));
		exit(1);
	}

	ptr = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == NULL)
	{
		fprintf(stderr, "%s failed to map size: %ld, %s\n", name, (long)buf.st_size, strerror(errno));
		exit(1);
	}

	if (buf.st_size < offset || buf.st_size < offset + length)
	{
		fprintf(stderr, "%s size: %ld, offset: %d, length: %d\n", name, (long)buf.st_size, offset, length);
		exit(1);
	}

	for (i = 0; i < length; i++)
	{
		ptr[offset + i] = value;
	}

	return 0;
}






