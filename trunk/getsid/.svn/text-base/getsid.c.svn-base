#include "apue.h"

int
main(int argc, char *argv[])
{
	fork();
	printf("process id: %d\n", getpid());
	printf("process group id: %d\n", getpgrp());
	printf("process group id: %d\n", getpgid(getpid()));
	printf("set process group id to : %d\n", getpid());
	if (setpgid(getpid(), getpid()))
		printf("set group id failed\n");
	printf("process group id: %d\n", getpgid(getpid()));
	printf("session id: %d\n", getsid(getpid()));
	exit(0);
}
