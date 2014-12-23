#include "apue.h"

#define HOME "HOME"
#define NEWHOME "HOME=/var/www"
int
main(int argc, char *argv[])
{
	char *tmp;
	
	tmp = getenv(HOME);
	fprintf(stderr, "%s: %s\n", HOME, tmp);
	fprintf(stderr, "%s: %s\n", HOME, getenv(HOME));
	tmp = NEWHOME;
	putenv(tmp);
	tmp = getenv(HOME);
	fprintf(stderr, "%s: %s\n", HOME, tmp);
	setenv(HOME, NEWHOME, 1);
	tmp = getenv(HOME);
	fprintf(stderr, "%s: %s\n", HOME, tmp);
	exit(0);
}
