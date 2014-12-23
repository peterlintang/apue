#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//#include <sys/dir.h>
#include <dirent.h>

#undef DEBUG
#define DEBUG
#if defined(DEBUG)
#define dprintf(fmt, args...) printf(fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
/*
*read the args and print the file type of each one
*/
int 
main(int argc, char *argv[])
{
	int i;
	struct stat filestatp;
//	DIR *dirp;
//	struct dirent *entry;
//	char *tmp;

	if (argc < 2)
	{
		printf("Usage\n");
		printf("\t%s dir\n", rindex(argv[0], '/') + 1);
		exit(1);
	}

/*	tmp = argv[1];

	dprintf("ls dir: %s\n", tmp);
	
	if ((dirp = opendir(tmp)) == NULL)
	{
		fprintf(stderr, "cant open dir: %s", tmp);
		exit(1);
	}
*/
//	while((entry = readdir(dirp)) != NULL)
	for (i = 1; i < argc; i++)	
	{
		fprintf(stdout, "filename: %s\n", argv[i]);
		if (stat(argv[i], &filestatp) < 0)
		{	
			fprintf(stderr, "open file %s fail\n", argv[i]);
			continue;
		}
		if (S_ISREG(filestatp.st_mode))
		{
			fprintf(stdout, "regular file\n");
		}
		else if (S_ISDIR(filestatp.st_mode))
		{
			fprintf(stdout, "directory\n");
		}
		else if (S_ISCHR(filestatp.st_mode))
		{
			fprintf(stdout, "char file\n");
		}
		else if (S_ISBLK(filestatp.st_mode))
		{
			fprintf(stdout, "block file\n");
		}
		else if (S_ISFIFO(filestatp.st_mode))
		{
			fprintf(stdout, "fifo file\n");
		}
		else if (S_ISSOCK(filestatp.st_mode))
		{
			fprintf(stdout, "socket file\n");
		}
		else if (S_ISLNK(filestatp.st_mode))
		{
			//seems it does not work
			fprintf(stdout, "link file\n");
		}
		else  
		{
			fprintf(stdout, "unknow file\n");
		}
	}

	exit(0);
}
