#include <stdio.h>
#include <stdlib.h>

/*
 * exchange three varbles's value;
 */
int main(int argc, char *argv[])
{
	int a, b, c;

	a = 0xaaaa;
	b = 0x5555;
	c = 0x2222;

	fprintf(stdout, "pre exchange : a = %x, b = %x, c = %x\n", a, b, c);

	c = a + c - (a = b, b = c);

	fprintf(stdout, "aft exchange : a = %x, b = %x, c = %x\n", a, b, c);

	return 0;
}
