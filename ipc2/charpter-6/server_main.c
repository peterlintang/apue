

/**
 *
 * 使用单个消息队列实现，一个进程负责从标准输入中获取文件名称，然后通过
 * 一条消息队列将文件名称发给另一进程；另一进程从消息队列获取文件名称后，
 * 打开文件并将文件内容通过另一消息队列发给前一进程，若出错，将错误信息
 * 返回给前一进程；
 *
 * 服务端
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/msg.h>


#define MAXLINE	1024

#define MSG_KEY1	1234L

#define FILE_MODE	S_IRUSR | S_IWUSR

void server(int , int);

int main(int argc, char *argv[])
{
	int msgfd;

	msgfd = msgget(MSG_KEY1, FILE_MODE | IPC_CREAT);

	server(msgfd, msgfd);

	return 0;
}

void server(int readfd, int writefd)
{
	size_t n;
	int fd;
	pid_t pid;
	char *ptr = NULL;
	struct msgbuf {
		long mtype;
		char mtext[MAXLINE];
	};

	struct msgbuf buf;

for ( ; ; )
{

	memset(&buf, 0, sizeof(buf));

	if ((n = msgrcv(readfd, &buf, MAXLINE, 1, 0)) <= 0)
		exit(1);

	buf.mtext[n] = '\0';

	if ((ptr = strchr(buf.mtext, ' ')) == NULL)
	{
		fprintf(stderr, "cant find pid, error format\n");
		continue;
	}
	*ptr++ = '\0';
	pid = atoi(buf.mtext);

//	fprintf(stdout, "get type: %ld, pid: %s, text: %s|\n", buf.mtype, buf.mtext, ptr);

	buf.mtype = pid;
	if ((fd = open(ptr, O_RDONLY)) < 0)
	{
		snprintf(buf.mtext + n, sizeof(buf.mtext) - n, ": cannt open, %s\n", strerror(errno));
		n = strlen(ptr);
		memmove(buf.mtext, ptr, n);
		msgsnd(writefd, &buf, n, 0);
	}
	else
	{
		while ((n = read(fd, buf.mtext, MAXLINE)) > 0)
		{
			msgsnd(writefd, &buf, n, 0);
		};

		close(fd);
	}

	msgsnd(writefd, &buf, 0, 0);

}

}





