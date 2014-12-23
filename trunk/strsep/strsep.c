
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *tmp = NULL;
	char *string = NULL;
	string = malloc(40 * sizeof(char));
	if (!string) {
		perror("malloc");
		exit(1);
	}
	strcpy(string, "hello->world");

	while(tmp = strsep(&string, "->")) {
		fprintf(stdout, "token: %s\n", tmp);
	//	fprintf(stdout, "token: %s\n", string);
	}
//	free(string);
	return 0;
}
