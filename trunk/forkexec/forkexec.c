#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>

int 
main(int argc, char *argv[])
{
	pid_t pid;
	uid_t uid;
	struct tms my_tms;
	clock_t my_clock;
	struct timeval my_timeval;
	struct rlimit my_rlimit;
	int i = 1;

	if ((pid = fork()) < 0)
	{
		printf("fork error!\n");
	}
	else if (pid == 0)
	{
		sleep(0);
		printf("in child!\n");
		printf("setting user id to 1001\n");
		if (setuid(1001) != 0)
			printf("set user id error\n");
		else
			printf("set ok\n");
		printf("i: %d\n", ++i);
		printf("pid: %d\nppid:%d\n", getpid(), getppid());
		printf("uid: %d\n", getuid());
		printf("euid: %d\n", geteuid());
		printf("pgrp: %d\n", getpgrp());
		//system("ls -l");
		printf("setting uid to 1000...\n");
		if (setuid(1000) !=0 )
		{
			printf("set uid fail\n");
		}
		else
		{
			printf("set uid success!\n");
			printf("uid: %d\n", getuid());
		}

		int j;
		pid_t cpid;
		for (j = 0; j < 5; j++)
		{
			if ((cpid = fork()) < 0)
				printf("fork error\n");
			else if (cpid == 0)
			{
				printf("fork %d\n", j);
				exit(0);
			}
		}
	}
	else
	{
		sleep(3);
		waitpid(pid, NULL, 0);
		printf("in parent!\n");
		printf("i: %0x\n", i);	
		printf("pid: %0d\nppid:%d\n", getpid(), getppid());
		printf("pgrp: %d\n", getpgrp());
		printf("uid: %0x\n", getuid());
		printf("euid: %0x\n", geteuid());
		printf("ticks per second:%lx\n", sysconf(_SC_CLK_TCK));
		printf("getting times...\n");
		my_clock = times(&my_tms);
		printf("my_clock: %lx\n", my_clock);
		printf("user time: %lx\n", my_tms.tms_utime);
		printf("sys time: %lx\n", my_tms.tms_stime);
		printf("\n");
		printf("login name: %s\n", getlogin());
		printf("getting timeval...\n");
		if ((gettimeofday(&my_timeval, NULL) != 0))
		{
			printf("gettimeofday error!\n");
			exit(1);
		}
		printf("time: %lx\n", my_timeval.tv_sec);
		printf("microseconds: %lx\n", my_timeval.tv_usec);
		printf("getting resource limit\n");
		if ((getrlimit(RLIMIT_AS, &my_rlimit)) != 0)
		{
			printf("get resource limit error!\n");
			exit(1);
		}
		printf("cur address space: %lx\n", my_rlimit.rlim_cur);
		printf("max address space: %lx\n", my_rlimit.rlim_max);
		my_rlimit.rlim_cur = 0xffff0000;
		my_rlimit.rlim_max = 0xffffffff;
		if ((setrlimit(RLIMIT_AS, &my_rlimit)) != 0)
		{
			printf("set address limit error!\n");
			exit(1);
		}
		if ((getrlimit(RLIMIT_AS, &my_rlimit)) != 0)
		{
			printf("get resource limit error!\n");
			exit(1);
		}
		printf("cur address space: %lx\n", my_rlimit.rlim_cur);
		printf("max address space: %lx\n", my_rlimit.rlim_max);
	}

	exit(0);
}
