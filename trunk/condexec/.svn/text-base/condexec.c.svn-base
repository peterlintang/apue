#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>

char *ENV[] = { "PATH=/usr/bin:/bin:/usr/sbin:/sbin",
				"NOVAMODULE_PATH=/usr/lib",
				"LD_LIBRARY_PATH=/usr/lib:/lib",
				NULL };

int main(int argc, char *argv[]) {

	struct stat sb;
	char **cmd_args = calloc(argc, sizeof(char *));
	int i = 0;
	char pid_fname[128];
	int pid_fd = 0;
	int c;
	int sleep_time = 0;
	unsigned long stack_cur = 0, stack_max = 0;
	char *cond_file = NULL;
	char *stack_size = NULL;
	char *token;
	int set_stack_size = 0;

	opterr = 0;

	while ((c = getopt (argc, argv, "w:c:s:")) != -1)
		switch (c)
		{
			case 'w':
				sleep_time = atoi(optarg);
				break;
			case 'c':
				cond_file = optarg;
				break;
			case 's':
				stack_size = optarg;
				token = strtok(stack_size, ",");
				if (token) {
					stack_cur = atoi(token);
					token = strtok(NULL, ",");
					stack_max = atoi(token);
				} else {
					fprintf( stderr, "-s <current,max>");
					exit (1);
				}
				if (!stack_cur)
					stack_cur = RLIM_INFINITY;
				if (!stack_max)
					stack_max = RLIM_INFINITY;
				set_stack_size = 1;
				break;
			case '?':
				if (isprint(optopt))
					fprintf( stderr, "Unknown option '-%c'.\n", optopt );
				else
					fprintf( stderr, "Unknown option character '\\x%x'.\n", optopt );
				exit(2);
			default:
				exit(3);
		}

	for(i = optind; i < argc; i++)
		cmd_args[i-optind] = argv[i];

	/* sleep until cond_file is there */
	while(stat(cond_file, &sb) != 0)
		sleep(sleep_time);

	sprintf(pid_fname, "/var/run/%s.pid", basename(argv[0]));
	pid_fd = open(pid_fname, O_WRONLY|O_CREAT);
	if(pid_fd > 0) {
		char pid[20];
		sprintf(pid, "%u\n", getpid());
		write(pid_fd, pid, strlen(pid)+1);
		close(pid_fd);
	}

	/* setrlimit */
	if (set_stack_size) {
		struct rlimit lim;
		lim.rlim_cur = stack_cur;
		lim.rlim_max = stack_max;
		if (setrlimit(RLIMIT_STACK, &lim) == -1) {
			fprintf( stderr, "setrlimit failed.\n");
			unlink(pid_fname);
			return -2;
		}
	}

	/* execve */
	if(execve(argv[optind], cmd_args, ENV) == -1) {
		unlink(pid_fname);
		return -1;
	}

	return 0; // not reached
}
