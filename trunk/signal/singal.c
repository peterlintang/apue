#include "apue.h"
#include <pwd.h>

#define DEBUG
#undef DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

//static void sig_usr(int signo);
static void my_alarm(int signo);

int
main(int argc, char *argv[])
{
/*
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		errprintf("can't catch SIGUSR1\n");
		exit(1);
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		errprintf("can't catch SIGUSR2\n");
		exit(1);
	}
	for (; ; )
	{
		pause();
		fprintf(stdout, "catch a singal\n");
	}
*/
	struct passwd *ptr;

	fprintf(stdout, "my_alarm address: %p\n", my_alarm);
	signal(SIGALRM, my_alarm);
	alarm(1);

	while (!pause()) 
		;
	fprintf(stdout, "wake up from pause \n");
	perror("pause");

	for (; ; )
	{
		if ((ptr = getpwnam("john")) == NULL)
		{
			errprintf("getpwnam error\n");
			exit(1);
		}
		if (strcmp(ptr->pw_name, "john") != 0)
		{
			errprintf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(1);
		}
		dprintf("ptr->pw_name: %s\n", ptr->pw_name);
		//printf("ptr->pw_name: %s\n", ptr->pw_name);
	}
	exit(0);
}

/*
static void
sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		fprintf(stdout, "received sigusr1\n");
//		exit(0);
	}
	else if (signo == SIGUSR2)
	{
		fprintf(stdout, "received sigusr2\n");
		exit(1);
	}
	else 
		fprintf(stdout, "unknow signal %d\n", signo);
}
*/
static void 
my_alarm(int signo)
{
//	struct passwd *rootptr;
	static int i = 0;
	fprintf(stdout, "in signal handler\n");
	signal(SIGALRM, my_alarm);
	fprintf(stdout, "i: %d\n", i++); 
//	if ((rootptr = getpwnam("root")) == NULL)
//	{
//		errprintf("getpwname root error\n");
//		exit(1);
//	}
//	dprintf("rootptr->pw_name: %s\n", rootptr->pw_name);
//	if (i == 5)
//		kill(getpid(), 9);
	alarm(1);
}





