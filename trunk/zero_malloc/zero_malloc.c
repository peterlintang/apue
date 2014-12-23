#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char *env[])
{
	char *ptr = NULL;
	int i;
	fprintf(stdout, "unsigned long: %d\n", sizeof(unsigned long));
	for (i = 0; env[i]; i++) 
		fprintf(stdout, "%4d\t%s\n", i, env[i]);

	ptr = malloc(0);
	if (ptr != NULL) fprintf(stdout, "\nmalloc ok ptr: %p\n", ptr);
	*ptr = 0x01;
	fprintf(stdout, "value %x\n", *ptr);
	return 0;
}
