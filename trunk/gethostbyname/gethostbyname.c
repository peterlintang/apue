/*
 * get host name by gethostbyname
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

void usage(char *prog)
{
	fprintf(stdout, "usage: %s hostname <like www.google.com>\n", prog);
	exit(0);
}


int main(int argc, char *argv[])
{
	char	*ptr;
	char 	**pptr;
	char	str[40];
	struct hostent *hptr;

	if (argc == 1)
		usage(argv[0]);

	while (--argc > 0) {
		ptr = *(++argv);
		if ((hptr = gethostbyname(ptr)) == NULL) {
			fprintf(stderr, "gethostbyname error for host: %s, %s\n", ptr, hstrerror(h_errno));
			continue;
		}

		fprintf(stdout, "official hostname : %s\n", hptr->h_name);
		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++) 
			fprintf(stdout, "\talias: %s\n", *pptr);

		switch (hptr->h_addrtype) {
		case AF_INET:
		case AF_INET6:
			pptr = hptr->h_addr_list;
			for (; *pptr != NULL; pptr++) {
				printf("\torigal address: %s", *pptr);
				printf("\taddress: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			}
			break;
		default:
			fprintf(stderr, "unknow address type\n");
			break;
		}
		
	}
	exit(0);
}
