/**********************************************
 *
 * implements the posix sem interfaces
 *
 * sem posix
 *
 * filename:	named-sem.h
 * *********************************************/
/*
 * implements the named semphore,
 * for process useage
 *
 * NOT TESTED YEAH
 */
#ifndef JOHN_LIN_NAMED_SEM
#define JOHN_LIN_NAMED_SEM

#include <semaphore.h>

#define CREATE_MODE	(S_IRUSR | S_IWUSR)


typedef struct __named_sem_t {
	char	*name;
	sem_t	*sem;
} named_sem_t;

int create_named_sem(const char *pathname, int flags, int res_num);
int destroy_named_sem(const char *pathname);
named_sem_t *open_named_sem(const char *pathname);
void close_named_sem(named_sem_t **psem);
int wait_named_sem(named_sem_t *psem, int nonblock);
int post_named_sem(named_sem_t *psem);



#endif // JOHN_LIN_NAMED_SEM
