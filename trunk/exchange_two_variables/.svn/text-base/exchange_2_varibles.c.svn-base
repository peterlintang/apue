
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a, b;

	a = 0x5555;
	b = 0xaaaa;

	fprintf(stdout, "pre exchange : a = %x, b = %x\n", a, b);
	
	a = a ^ b;
	b = b ^ a;
	a = a ^ b;

	fprintf(stdout, "after exchange : a = %x, b = %x\n", a, b);

	return 0;
}
