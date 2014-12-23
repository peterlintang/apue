#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char *argv[])
{
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "b:s:w:")) != -1)                        // opterr optarg optind optopt four arguments
	{
		switch (c)
		{
			case 'b':
				fprintf(stderr, "b: %s\n", optarg);
				break;
			case 's':
				fprintf(stderr, "s: %s\n", optarg);
				break;
			case 'w':
				fprintf(stderr, "w: %s\n", optarg);
				break;
			default:
				if (isprint(optopt))
					fprintf(stderr, "error: unknow: %c\n", optopt);
				else
					fprintf(stderr, "error: unknow: \\x%x\n", optopt);
				break;
		}
	}

	printf("returning\n");
	return 0;
}
