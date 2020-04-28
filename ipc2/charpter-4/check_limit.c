
/*
 * 查看系统的pipe buf, open max限制
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "%s arg\n", argv[0]);
		exit(0);
	}

	fprintf(stdout, "PIPE_BUF = %ld, OPEN_MAX = %ld\n", 
					pathconf(argv[1], _PC_PIPE_BUF), sysconf(_SC_OPEN_MAX));

	return 0;
}
