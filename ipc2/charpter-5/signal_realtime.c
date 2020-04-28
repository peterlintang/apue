
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>

static void sig_rt(int signo, siginfo_t *info, void *context)
{
	fprintf(stdout, "received signo = %d, code = %d, ival = %d\n",
				signo, info->si_code, info->si_int);
}

int main(int argc, char *argv[])
{
	int i;
	int j;
	sigset_t newset;
	union sigval val;
	pid_t pid;
	struct sigaction act;

	fprintf(stdout, "SIGRTMIN = %ld, SIGRTMAX = %ld\n", (long)SIGRTMIN, (long)SIGRTMAX);

	if ((pid = fork()) == 0)
	{
		sigemptyset(&newset);
		sigaddset(&newset, SIGRTMAX);
		sigaddset(&newset, SIGRTMAX - 1);
		sigaddset(&newset, SIGRTMAX - 2);
		sigprocmask(SIG_BLOCK, &newset, NULL);

		memset(&act, 0, sizeof(act));
		act.sa_sigaction = sig_rt;
		act.sa_flags |= SA_SIGINFO;
		sigemptyset(&act.sa_mask);

		sigaction(SIGRTMAX, &act, NULL);
		sigaction(SIGRTMAX - 1, &act, NULL);
		sigaction(SIGRTMAX - 2, &act, NULL);

		sleep(6);
		sigprocmask(SIG_UNBLOCK, &newset, NULL);
		sleep(3);
		exit(0);

	}

	sleep(3);
	for (i = SIGRTMAX - 2; i <= SIGRTMAX ; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			val.sival_int = j;
			sigqueue(pid, i, val);
			fprintf(stdout, "sent signal %d, val = %d\n", i, j);
		}
	}

	return 0;
}

typedef void sigfunc_rt(int, siginfo_t *info, void *);

sigfunc_rt *signal_rt(int signo, sigfunc_rt *fun)
{
	struct sigaction act;
	struct sigaction oact;

	act.sa_sigaction = fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}

	if (sigaction(signo, &act, &oact) < 0)
		return (sigfunc_rt *)SIG_ERR;
	return oact.sa_sigaction;
}



