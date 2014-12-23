#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


void printusage(char *prog)
{
	fprintf(stdout, "%s \n", prog);
}

int 
main(int argc, char *argv[])
{
	int result;
	char *str = "hello world";
	//char *str = argv[1];
	char *ptr = NULL;

	if ((ptr = strchr(str, 'w')))
	{
		fprintf(stdout, "locate %c\n", *ptr);
	} 
	else 
	{
		fprintf(stderr, "error to locate \n");
		exit(1);
	}

// dup a string
	ptr = strdup(str);
	fprintf(stdout, "new string: %s\n", ptr);
	fprintf(stdout, "test: %s\n", __STRING(523489h));

	exit(0);
}
