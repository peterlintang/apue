
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
void exit_fun(void);

int
main(int argc, char *argv[])
{
	int i;
	
	for (i = 0; i < 32; i++)
		if (atexit(exit_fun) != 0)
			fprintf(stderr, "atexit error\n");
	printf("hello world\n");
//	exit(main(argc, argv));
}

void exit_fun(void)
{
	static int i = 0;
	fprintf(stderr, "exiting %d\n", i++);
}
