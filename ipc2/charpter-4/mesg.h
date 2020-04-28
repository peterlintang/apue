
#ifndef MY_MESG_H__
#define MY_MESG_H__


#define PIPE_BUF	1024

#define MAXMESGDATA (PIPE_BUF - 2 * sizeof(long))

#define MESGHDRSIZE	(sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
};

ssize_t mesg_send(int fd, struct mymesg *msg);
ssize_t mesg_send(int fd, struct mymesg *msg);



#endif // MY_MESG_H__
