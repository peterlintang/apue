

/**
 *
 * 使用单个消息队列实现，一个进程负责从标准输入中获取文件名称，然后通过
 * 一条消息队列将文件名称发给另一进程；另一进程从消息队列获取文件名称后，
 * 打开文件并将文件内容通过另一消息队列发给前一进程，若出错，将错误信息
 * 返回给前一进程；
 *
 * 客户端
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <fcntl.h>


#define MAXLINE	1024

#define MSG_KEY1	1234L

#define FILE_MODE	S_IRUSR | S_IWUSR

void client(int , int);

int main(int argc, char *argv[])
{
	int msgfd;

	msgfd = msgget(MSG_KEY1, FILE_MODE);

	client(msgfd, msgfd);

	return 0;
}

void client(int readfd, int writefd)
{
	size_t len = 0;
	size_t n = 0;
	struct msgbuf {
		long mtype;
		char mtext[MAXLINE];
	};
	struct msgbuf buf;

	memset(&buf, 0, sizeof(buf));

	snprintf(buf.mtext, MAXLINE, "%ld ", (long)getpid());
	len = strlen(buf.mtext);

	fgets(buf.mtext + len, MAXLINE - len, stdin);
	len = strlen(buf.mtext);
	if (buf.mtext[len - 1] == '\n')
		len--;

//	fprintf(stdout, "send: %s|\n", buf.mtext);

	buf.mtype = 1;
	msgsnd(writefd, &buf, len, 0);

	while ((n = msgrcv(readfd, &buf, MAXLINE, 0, 0)) > 0)
		write(STDOUT_FILENO, buf.mtext, n);
}

