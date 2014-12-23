
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */
#include <signal.h>	/* for SIGUSRx */
#include <errno.h>	/* for errno */

#define FILE_MODE S_IRUSR | S_IWUSR


int	pipefd[2];
static void sig_usr1(int signo);

int main(int argc, char **argv)
{
	int	nfds;
	char	c;
	fd_set	rset;
	mqd_t	mqd;
	void	*buff;
	ssize_t	n;
	struct mq_attr	attr;
	struct sigevent sigev;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: select-mq <name>\n", __func__);
		exit(1);
	}

	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
	if (mqd == -1) {
		perror("mq_open");
		exit(2);
	}

	mq_getattr(mqd, &attr);
	buff = malloc(attr.mq_msgsize);

	pipe(pipefd);

	signal(SIGUSR1, sig_usr1);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo  = SIGUSR1;
	mq_notify(mqd, &sigev);

	FD_ZERO(&rset);

	for (; ; ) {
		FD_SET(pipefd[0], &rset);
		nfds = select(pipefd[0] + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(pipefd[0], &rset)) {
			read(pipefd[0], &c, 1);
			mq_notify(mqd, &sigev);
			while ((n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) >= 0) {
				fprintf(stdout, "<%s> read %d bytes\n", __func__, n);
			}
			if (errno != EAGAIN) {
				perror("mq_receive");
				exit(3);
			}
		}
	}

	return 0;
}

static void sig_usr1(int signo)
{
	write(pipefd[1], " ", 1);
	return ;
}
