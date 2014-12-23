/*
 * implements execute client
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* for memset */
#include "server.h"
#include "client.h"


int main(int argc, char **argv)
{
	int		count = 0; /* for test */
	char		buf[200];
	client_t 	*client 	= NULL;

	fprintf(stdout, "%s: %s\n", __func__, buf);
	memset(buf, 0, 200);

	client = new_client(AF_INET, SERVER_PORT, IP_STR);
	fprintf(stdout, "%s: client %p\n", __func__, client);
	if (!client) {
		fprintf(stderr, "%s: create new client failed\n", __func__);
		exit(2);
	}

	show_client_info(client, 1);

	fprintf(stdout, "%s: %d\n", __func__, count++);

	if (connect_to_server_tcp(client) == 1) {
		fprintf(stdout, "connect to server OK\n");
		fprintf(stdout, "recving mesg from server...\n");
		fprintf(stdout, "recv mesg (%d) %s\n", recv_mesg_from_server_tcp(client, buf, 200), buf);
	} else {
		fprintf(stderr, "%s: connect to server failed\n", __func__);
		fprintf(stdout, "%s: client %p\n", __func__, client);
//		exit(3);
	}
	
	destroy_client(&client);
	fprintf(stdout, "%s: exiting from main\n", __func__);
	exit(0);
}
