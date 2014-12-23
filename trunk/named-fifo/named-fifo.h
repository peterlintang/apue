
/*
 *
 * implement the named fifo for processes 
 * communicate
 *
 */

#ifndef JOHN_LIN_NFIFO_H__
#define JOHN_LIN_NFIFO_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define JOHN_LIN_NFIFO_ACCESS_MODE	(S_IRUSR | S_IWUSR)
typedef struct __named_fifo_t {
	char	*pathname;
	int	fd;
} named_fifo_t;

int create_named_fifo(const char *pathname);
int destroy_named_fifo(const char *pathname);
named_fifo_t *open_named_fifo(const char *pathname, mode_t mode);
void close_named_fifo(named_fifo_t **ppnfifo);
int read_named_fifo(named_fifo_t *nfifo, char *buf, int len);
int write_named_fifo(named_fifo_t *nfifo, const char *buf, int len);

#endif  // JOHN_LIN_NFIFO_H__
