#include <fcntl.h>
#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif

#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int
main(int argc, char *argv[])
{
	/*show access*/
	if (argc != 2)
	{
		errprintf("Usage: a.out <pathname>\n");
		exit(1);
	}
	
	if (access(argv[1], R_OK) < 0)
	{
		errprintf("access error for %s\n", argv[1]);
		exit(1);
	}
	else
		dprintf("read access ok\n");
	
	if (open(argv[1], O_RDONLY) < 0)
	{
		errprintf("open error for %s\n", argv[1]);
		exit(1);
	}
	else
		dprintf("open for reading ok\n");
	
	
	/*show umask*/
	umask(0);
	if (creat("foo", RWRWRW) < 0)
	{
		errprintf("create error for foo");
		exit(1);
	}
	
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
	{
		errprintf("creat error for bar");
		exit(1);
	}


	/*show chmod*/
	struct stat statbuf;

	if (stat("foo", &statbuf) < 0)
	{
		errprintf("stat error for foo");
		exit(1);
	}
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
	{
		errprintf("chmod error for foo");
		exit(1);
	}
	dprintf("foo file size: %d\n", statbuf.st_size);

	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
	{
		errprintf("chmod error for bar");
		exit(1);
	}

	system("sh ./test.sh johnlin\n ls -l");

	exit(0);

}
