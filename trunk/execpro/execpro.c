#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#define	dprintf(fmt, args...) printf(fmt, ##args)
#else
#define dprintf(fmt, args...)  
#endif


void usage(char *argv);



int
main(int argc, char *argv[])
{
	int i;
	char buf[1024]; 

	memset(buf, 0, sizeof(char) * 1024);

	if (argc < 2)
	{
		usage((char *)basename(argv[0]));
		exit(1);
	}

	for (i = 1; i < argc ; i++)
	{
		dprintf("argv %d: %s\n", i, argv[i]);
		sprintf(buf + strlen(buf), "%s ", argv[i]);
		dprintf("buf: %s\n", buf);
	}
	sprintf(buf + strlen(buf), "\n");
	dprintf("execute: %s\n", buf);
	
	if (system(buf) < 0)
	{
		fprintf( stderr, "system error!\n");
	}
	else 
	{
		fprintf( stdout, "exec OK\n");
	}

	exit(0);
}

void usage(char *argv)
{
	fprintf( stderr, "Usage: \n");
	fprintf( stderr, "\t%s arguments\n", argv);
}
