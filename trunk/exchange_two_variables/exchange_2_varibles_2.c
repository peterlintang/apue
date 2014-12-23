
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a, b;

	a = 0xaaaa;
	b = 0x5555;

	fprintf(stdout, "pre exchange : a = %x, b = %x\n", a, b);

	a = a + b;
	b = a - b;
	a = a - b;

	fprintf(stdout, "aft exchange : a = %x, b = %x\n", a, b);

	return 0;
}
