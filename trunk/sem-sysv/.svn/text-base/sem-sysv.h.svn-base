
/*
 * implements the system v semaphore interfaces
 *
 * filename:		sem-sysv.h
 */

#ifndef JOHN_LIN_SEM_SYSV_H__
#define JOHN_LIN_SEM_SYSV_H__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

/*
typedef struct __sem_sysv_t {
	char	*pathname;
	int	id;
	int	semid;
} sem_sysv_t;
*/

int create_sem_sysv(const char *pathname, int id, int res_num);
int destroy_sem_sysv(const char *pathname, int id);
int open_sem_sysv(const char *pathname, int id);
void close_sem_sysv(int semid);
int get_sem_sysv(int semid);
int release_sem_sysv(int semid);

#endif // JOHN_LIN_SEM_SYSV_H__
