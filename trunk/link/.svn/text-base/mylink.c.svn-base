#include "apue.h"
#include <fcntl.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...) 
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define UNLINKFILE  "tempfile.txt"

int
main(int argc, char *argv[])
{
	if (open(UNLINKFILE, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH) < 0)
	{
		errprintf("can't open file %s\n", UNLINKFILE);
		exit(1);
	}

	/*test rename file function*/
	if (rename(UNLINKFILE, "hello.txt") < 0)
	{
		errprintf("can't rename file: %s\n", UNLINKFILE);
		exit(1);
	}
	
	sleep(4);

	/*test unlink funciton*/
	if (unlink(UNLINKFILE) < 0)
	{
		errprintf("unlink file %s error\n", UNLINKFILE);
		exit(1);
	}

	/*test remvoe function*/
	if (remove(UNLINKFILE) < 0)
	{
		errprintf("remove file %s error\n", UNLINKFILE);
		exit(1);
	}

	dprintf("file: %s unlinked\n", UNLINKFILE);
	sleep(1);
	dprintf("done\n");
	exit(0);
}

