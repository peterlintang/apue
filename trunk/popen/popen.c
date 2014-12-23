
#include "apue.h"

#define		CMD	"ls -l"

int main(int argc, char *argv[])
{
	FILE *file;
	char line[MAXLINE];

	fprintf(stdout, "\ngoing to excute ...\n");
	if(!(file = popen(CMD, "r")))
		perror("popen");
	while (fgets(line, MAXLINE, file) != NULL) 
		fprintf(stdout, "%s", line);
	fprintf(stdout, "\nOK\n");
	pclose(file);

	return 0;
}
