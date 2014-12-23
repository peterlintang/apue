#include "apue.h"
#include <sys/socket.h>


#if defined S_PIPE_USE_PIPE
/*
 *returns a streams-based pipe, with the two file descriptors
 *returned in fd[0] and fd[1].
 */
int
s_pipe(int fd[2])
{
	return (pipe(fd));
}

#else
/* 
 *returns a full-duplex "stream" pipe (a unix domain socket).
 *with the two file descriptors returned in fd[0] and fd[1].
 */
int
s_pipe(int fd[2])
{
	return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
#endif
