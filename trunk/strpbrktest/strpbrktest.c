#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char *p = "Find all vowels";

	while (p)
	{
		printf("%s\n", p);
		p = strpbrk(p+1, "aeiouAEIOU");
	}

	exit(0);
}
