
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	fprintf(stdout, "1024 / (8 * sizeof(unsigned long int)): %d\n", 1024 / (8 * sizeof(unsigned long int)));
	return 0;
}
