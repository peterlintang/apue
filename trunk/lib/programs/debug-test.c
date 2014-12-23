
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

uint32_t DebugLevel = 6;

int main(int argc, char *argv[])
{
	int	ret = 0;

	DEBUGP(DERROR, "main", "%s - %s\n", "hello", "john");
	return ret;
}
