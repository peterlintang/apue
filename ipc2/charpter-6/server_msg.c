

/**
 *
 * 使用消息队列实现，一个进程负责从标准输入中获取文件名称，然后通过
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
#define MSG_KEY2	2345L

#define FILE_MODE	S_IRUSR | S_IWUSR

void server(int , int);

int main(int argc, char *argv[])
{
	int readfd;
	int writefd;

	readfd = msgget(MSG_KEY1, FILE_MODE | IPC_CREAT);
	writefd = msgget(MSG_KEY2, FILE_MODE | IPC_CREAT);

	server(readfd, writefd);

	return 0;
}

void server(int readfd, int writefd)
{
	size_t n;
	int fd;
	struct msgbuf {
		long mtype;
		char mtext[MAXLINE];
	};

	struct msgbuf buf;

	memset(&buf, 0, sizeof(buf));

	if ((n = msgrcv(readfd, &buf, MAXLINE, 0, 0)) <= 0)
		exit(1);

	buf.mtext[n] = '\0';
//	fprintf(stdout, "get type: %ld, text: %s\n", buf.mtype, buf.mtext);

	if ((fd = open(buf.mtext, O_RDONLY)) < 0)
	{
		snprintf(buf.mtext + n, sizeof(buf) - n, ": cannt open, %s\n", strerror(errno));
		n = strlen(buf.mtext);
		buf.mtype = 1;
		msgsnd(writefd, &buf, n, 0);
	}
	else
	{
		while ((n = read(fd, buf.mtext, MAXLINE)) > 0)
		{
			buf.mtype = 1;
			msgsnd(writefd, &buf, n, 0);
		};

		close(fd);
	}

	buf.mtype = 1;
	msgsnd(writefd, &buf, 0, 0);
}





