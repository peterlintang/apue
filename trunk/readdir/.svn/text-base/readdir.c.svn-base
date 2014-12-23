#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) printf(fmt, ##args)
#else
#define dprintf(fmt, args...) 
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

int 
main(int argc, char *argv[])
{
	struct dirent *entry;
	DIR *dirp;
	char *buf;

/*	if (argc > 2)
	{
		printf("Usage:\n");
		printf("\t%s dir\n",rindex(argv[0],'/') + 1);
		exit(1);
	}
*/
	
	if (argc == 1)
		buf = (char *)dirname(argv[0]);
	else
		buf = argv[1];
	
	dprintf("dir: %s\n", buf);

	if ((dirp = opendir(buf)) == NULL)
	{
		fprintf(stderr, "open dir failed!\n");
		exit(1);
	}

	while ((entry = readdir(dirp)) != NULL)
	{
		fprintf(stdout, "%s\n", entry->d_name);
	}
	closedir(dirp);

	if (entry == NULL)
	{
		dprintf("entry equals NULL\n");
	}

	char *tmp = NULL;
	tmp = malloc(PATH_MAX + 1);

	if (!tmp)
	{
		errprintf("malloc error\n");
		exit(1);
	}
	
	if (getcwd(tmp, PATH_MAX) == NULL)
	{
		errprintf("getcwd error\n");
		exit(1);
	}
	else
	{
		dprintf("current work dir: %s\n", tmp);
	}
	free(tmp);


	exit(0);
}
