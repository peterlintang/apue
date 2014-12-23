#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

int my_strlen(const char *s)
{
	int i = 0;

	for (; s[i] != '\n'; i++)
		;
	return i;
}

char *my_index(const char *s, int c)
{
	int i, length = my_strlen (s);
	const char *ptr = s;

	for (i = 0; i < length; i++)
	{	if (ptr[i] == c)
		{
			printf("\n...find in %d....\n", i);
			return (char *)(ptr + i);
		}
	}

	return NULL;
}


char *my_rindex(const char *s, int c)
{
	int i, length = my_strlen (s);
	const char *ptr = s;

	for (i = length - 1; i >= 0; i--)
	{
		if (ptr[i] == c)
		{
			printf("\nfind in %d\n", i);
			return (char *)(ptr + i);
		}
	}

	return NULL;
}
