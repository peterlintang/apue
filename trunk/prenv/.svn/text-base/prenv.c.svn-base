#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char * argv[])
{
	char **tmp;
	extern char **environ;

	printf("hello world!\n");
	printf("environs:\n");
	for (tmp = environ; *tmp != NULL; tmp++)
	{
		printf("\t%s\n", *tmp);
	}
	exit(0);
}
