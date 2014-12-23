#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

int
main(int argc, char *argv[])
{
	pid_t pid;

	vfork();
/*	if ((pid = getpid()) < 0)
	{
		errprintf("getpid error\n");
		exit(1);
	}
	else
	{
		printf("pid : %d\n", pid);
	}
*/
	printf("pid   : %d\n", getpid());
	printf("ppid  : %d\n", getppid());
	printf("uid   : %d\n", getuid());
	printf("euid  : %d\n", geteuid());
	printf("gid   : %d\n", getgid());
	printf("egid  : %d\n", getegid());

	exit(0);
}
