


/*
 *
 * use a stream to read 
 * and write
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == 'V') {
			ungetc(c, stderr);
			fprintf(stdout, "unget %c\n", c);
		}
		putchar(c);
	}

	if (ferror(stdin)) 
		fprintf(stdout, "read error from stdin\n");
	else if (feof(stdin))
		fprintf(stdout, "end of file\n");
	else
		fprintf(stdout, "unknow error\n");
	
	return 0;
		
}
