
/*
 *
 * implements the posix shared memory interfaces
 *
 */

#ifndef JOHN_LIN_POSIX_SHM_H__
#define JOHN_LIN_POSIX_SHM_H__

typedef struct _p_shm_t {
	char	*name,
	void	*addr;
	int	fd;
} p_shm_t;

int create_p_shm(const char *name);
int destroy_p_shm(const char *name);
p_shm_t *open_shm(const char *name, mode_t mode);
void close_shm(p_shm_t **pshm);

#endif  // JOHN_LIN_POSIX_SHM_H__
