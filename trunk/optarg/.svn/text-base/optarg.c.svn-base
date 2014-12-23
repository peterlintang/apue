#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/*
*analize option args
*/
int 
main(int argc, char *argv[])
{
	int c;

	while ((c = getopt(argc, argv, "s:c")) != -1)
	{
		switch (c)
		{
			case 'c':
				printf("find c\n");
				printf("optarg: %s\n", optarg);	
				printf("optind: %d\n", optind);
				printf("opterr: %d\n", opterr);
				printf("optopt: %d\n", optopt);
				break;
			case 's':
				printf("find s\n");
				printf("optarg: %s\n", optarg);	
				printf("optind: %d\n", optind);
				printf("opterr: %d\n", opterr);
				printf("optopt: %d\n", optopt);
				break;
			default:
				printf("not find\n");
				printf("optarg: %s\n", optarg);	
				printf("optind: %d\n", optind);
				printf("opterr: %d\n", opterr);
				printf("optopt: %d\n", optopt);
				break;
		}
	}
	
	exit(0);
}



