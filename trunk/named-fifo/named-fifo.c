
/*
 *
 * implement the named fifo interfaces
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// for access 
#include <string.h>		// for strdup

#include "named-fifo.h"

int create_named_fifo(const char *pathname)
{
	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	if (mkfifo(pathname, JOHN_LIN_NFIFO_ACCESS_MODE) == -1) {
		perror("mkfifo");
		return -1;
	}

	fprintf(stdout, "create named fifo: %s\n", pathname);
	return 0;
}

int destroy_named_fifo(const char *pathname)
{
	struct stat sbuf;

	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return -3;
	}

	if (access(pathname, F_OK) == -1) {
		perror("access");
		return -2;
	}

	if (stat(pathname, &sbuf) == -1) {
		perror("stat");
		return -1;
	}

	if (S_ISFIFO(sbuf.st_mode)) {
		unlink(pathname);
		fprintf(stdout, "unlink %s ok\n", pathname);
	} else {
		fprintf(stderr, "%s is not fifo file\n", pathname);
	}

	return 0;
}
	

named_fifo_t *open_named_fifo(const char *pathname, mode_t mode)
{
	named_fifo_t *nfifo = NULL;

	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return NULL;
	}

	if (!(nfifo = calloc(1, sizeof(*nfifo)))) {
		perror("calloc");
		return NULL;
	}

	if (!(nfifo->pathname = strdup(pathname))) {
		perror("strdup");
		free(nfifo);
		return NULL;
	}

	fprintf(stdout, "<%s> hello llsd\n", __func__);
	if ((nfifo->fd = open(pathname, mode)) == -1) {
		perror("open");
		free(nfifo->pathname);
		free(nfifo);
		return NULL;
	}

	fprintf(stdout, "opened fifo: %s , fd: %d\n", 
			nfifo->pathname, nfifo->fd);
	return nfifo;
}

void close_named_fifo(named_fifo_t **ppnfifo)
{
	named_fifo_t *nfifo = NULL;

	if (ppnfifo && *ppnfifo) {
		nfifo = *ppnfifo;
		fprintf(stdout, "close fifo: %s, fd: %d\n",
				nfifo->pathname, nfifo->fd);
		close(nfifo->fd);
		free(nfifo->pathname);
		free(nfifo);
		*ppnfifo = NULL;
	}
}

int read_named_fifo(named_fifo_t *nfifo, char *buf, int len)
{
	int	read_len  = 0;
	int	total_len = 0;
	
	if (!nfifo || !buf) {
		fprintf(stderr, "arguments error\n");
		return -3;
	}

	if (nfifo->fd < 0) {
		fprintf(stderr, "not open path: %s, fd: %d\n",
			nfifo->pathname, nfifo->fd);
		return -2;
	}
	fprintf(stdout, "<%s> hello llsd\n", __func__);

	if ((read_len = read(nfifo->fd, &total_len, sizeof(int))) == -1) {
		perror("read");
		return -1;
	}

	if (total_len > len) {
		fprintf(stderr, "data(%d bytes) is too large for buf(%d bytes) to store\n", 
				total_len, len);
		return -4;
	}

	len = total_len;
	total_len = 0;
	fprintf(stdout, "going to read %d bytes from %s\n", len, nfifo->pathname);
	while (total_len < len) {
		read_len = read(nfifo->fd, buf + total_len, len - total_len);
		if (read_len == -1) {	// ignore intre, just return -1
			perror("read");
			return -1;
		}
		if (read_len == 0) break;
		total_len  += read_len;
	}

	return total_len;
}

int write_named_fifo(named_fifo_t *nfifo, const char *buf, int len)
{
	int	write_len = 0;
	int	total_len = 0;

	if (!nfifo || !buf || len < 0) {
		fprintf(stderr, "arguments error\n");
		return -3;
	}

	if (nfifo->fd < 0) {
		fprintf(stderr, "not open path: %s, fd: %d\n",
			nfifo->pathname, nfifo->fd);
		return -2;
	}
	fprintf(stdout, "<%s> hello llsd\n", __func__);

	if ((write_len = write(nfifo->fd, &len, sizeof(int))) == -1) {
		perror("write");
		return -1;
	}

	fprintf(stdout, "going to write %d bytes to path %s\n", len, nfifo->pathname);
	while (total_len < len) {
		write_len = write(nfifo->fd, buf + total_len, len - total_len);
//		if (write_len == -1) {
		if (write_len <= 0) {	// just ignore intr and return -1
			perror("write");
			return -1;
		}

//		if (write_len == 0) break;

		total_len += write_len;
	}

	return total_len;
}



