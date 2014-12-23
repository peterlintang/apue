
/*
 * test the named fifo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "named-fifo.h"

#define FIFO_NAME	"./hello-world"

int main(int argc, char *argv[])
{
	int	read_len = 0;
	char	buf[256];
	named_fifo_t *nfifo = NULL;

	if (create_named_fifo(FIFO_NAME) != 0) {
		exit(1);
	}

	if (!(nfifo = open_named_fifo(FIFO_NAME, O_WRONLY))) {
		destroy_named_fifo(FIFO_NAME);
		exit(2);
	}

	write_named_fifo(nfifo, "hello john lin\n", 13);
/*
	read_len = read_named_fifo(nfifo, buf, 256);
	if (read_len > 0) buf[read_len] = '\0';
	fprintf(stdout, "get freom fifo: %s\n", buf);
*/

	sleep(4);
	close_named_fifo(&nfifo);
	destroy_named_fifo(FIFO_NAME);

	return 0;
}
