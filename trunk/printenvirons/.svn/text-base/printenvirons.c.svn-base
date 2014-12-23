#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int 
main(int argc, char * argv[])
{
	char **tmp;
	extern char **environ;
	char buf[1024];
	struct rlimit my_limit;

	printf("current work dir: %s\n", getcwd(buf, 1024));
	printf("what is in buf: %s\n", buf);
	sleep(1);
	printf("get current dir: %s\n", (char *)get_current_dir_name());
	printf("environ add: %0x\n", (int )&environ);
	sleep(1);
	printf("first environ add: %0x\n", (int )environ);
	printf("environs:\n");
	usleep(1024);
	for (tmp = environ; *tmp != NULL; tmp++)
	{
		printf("\taddress: %0x\n", (int )tmp);
		printf("\t%s\n", *tmp);
	 	sleep(0);
	}
	printf("\taddress: %0x\n", (int )tmp);
	printf("\t%s\n", *tmp);

	if (getrlimit(RLIMIT_CPU, &my_limit) < 0)
		fprintf(stderr, "getrlimit error!\n");
	else
		printf("cpu limit: %10ld\n", my_limit.rlim_cur);
	if (getrlimit(RLIMIT_FSIZE, &my_limit) < 0)
		fprintf(stderr, "getrlimit error!\n");
	else
		printf("fsize limit: %10ld\n", my_limit.rlim_cur);
	printf("pid: %d\n", getpid());
	printf("ppid: %d\n", getppid());

	exit(0);
}
