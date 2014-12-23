
/*
 * implements the unix sock server's interfaces
 * filename:	udsock-server.c
 */

#include "udsock-server.h"

unix_sock_server *create_unix_sock_server(const char *pathname, int backlog)
{
	struct sockaddr_un addr;
	unix_sock_server *us = NULL;

	if (!pathname || backlog < 1) {
		fprintf(stderr, "arguments error\n");
		return NULL;
	}
	
	if (!(us = calloc(1, sizeof(*us)))) {
		fprintf(stderr, "can not allocat memory for new unix_sock_t\n");
		return NULL;
	}

	if ((us->listen_sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		free(us);
		return NULL;
	}
	us->path 	= strdup(pathname);
	us->backlog 	= backlog;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family	= AF_UNIX;
	sprintf(addr.sun_path, "%s", us->path);
	if ((bind(us->listen_sock, (const struct sockaddr *)&addr, 
		sizeof(addr)) < 0) || (listen(us->listen_sock, us->backlog))) {
		fprintf(stderr, "can not bind or listen to socket: %d with addr: %s",
				us->listen_sock, us->path);
		close(us->listen_sock);
		free(us->path);
		free(us);
		return NULL;
	}


	fprintf(stdout, "create listen  sock: %d backlog: %d path: %s ok\n",
			us->listen_sock, us->backlog, us->path);
	return us;
}

void destroy_unix_sock_server(unix_sock_server **uspp)
{
	unix_sock_server *us = NULL;
	if (uspp && (us = *uspp)) {
		fprintf(stdout, "destroy listen  sock: %d backlog: %d path: %s ok\n",
			us->listen_sock, us->backlog, us->path);
		if (us->listen_sock != -1)
			close(us->listen_sock);
		if (access(us->path, F_OK) == 0) 
			unlink(us->path);	// remove the file
		free(us->path);
		free(us);
		*uspp = NULL;
	}
}

/*
 * accept new clients to connect to server, will block
 */
unix_sock_client *unix_sock_accept_server(unix_sock_server *server)
{
	unix_sock_client *client = NULL;

	if (!server) {
		fprintf(stderr, "arguments error\n");
		return NULL;
	}

	if (!(client = create_unix_sock_client(server->path))) {
		fprintf(stderr, "can not create new client for accept\n");
		return NULL;
	}

	if ((client->conn_sock = accept(server->listen_sock, 
					NULL, NULL)) == -1) {
		perror("accept");
		destroy_unix_sock_client(&client);
		return NULL;
	}

	fprintf(stdout, "new client connect to server, fd: %d\n", 
			client->conn_sock);
	return client;
}


int unix_sock_send_server(unix_sock_client *client, char *buf, unsigned int len)
{
	if (!client || !buf) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	return unix_sock_send_client(client, buf, len);
}

int unix_sock_recv_server(unix_sock_client *client, char *buf, unsigned int len)
{
	if (!client || !buf) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	return unix_sock_recv_client(client, buf, len);
}




