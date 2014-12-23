
/*
 * implements the system v semaphore interfaces
 *
 * filename:	sem-sysv.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sem-sysv.h"

int create_sem_sysv(const char *pathname, int id, int res_num)
{
	key_t	key;
	int	semid;
	int	flags = 0;
 	union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
         } tmp;


	if (!pathname || res_num < 1) {
		fprintf(stderr, "arguments error, path: %s, res num: %d\n",
				pathname, res_num);
		return -2;
	}

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return -1;
	}

	flags = (IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	//if ((semid = semget(key, res_num, flags)) == -1) {
	if ((semid = semget(key, 1, flags)) == -1) {
		perror("semget");
		return -1;
	}

	tmp.val = res_num;
	if (semctl(semid, 0, SETVAL, tmp) == -1) {
		perror("semctl");
		close(semid);
		return -1;
	}

	close(semid);
	fprintf(stdout, "<%s> create sys v semaphore\n", __func__);
	fprintf(stdout, "<%s> path: %s, id: %d, res num: %d\n", 
			__func__, pathname, id, res_num);
	fprintf(stdout, "<%s> key: %d, id: %d\n", __func__, key, semid);

	return 0;
}

int destroy_sem_sysv(const char *pathname, int id)
{
	key_t	key;
	int	semid;
	int	flags = 0;

	if (!pathname) {
		fprintf(stderr, "arguments error, path: %s\n",
				pathname);
		return -2;
	}

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return -1;
	}

	flags = O_RDWR | S_IRUSR | S_IWUSR;
	//if ((semid = semget(key, res_num, flags)) == -1) {
	if ((semid = semget(key, 1, flags)) == -1) {
		perror("semget");
		return -1;
	}

	if (semctl(semid, 0, IPC_RMID, 0) == -1) { // will remove immediately, 
				//and wake up other processes waiting on semop
		perror("semctl");
		return -1;
	}

	close(semid);
	return unlink(pathname);
}

int open_sem_sysv(const char *pathname, int id)
{
	key_t	key;
	int	semid;
	int	flags = 0;

	if (!pathname) {
		fprintf(stderr, "arguments error, path: %s\n",
				pathname);
		return -2;
	}

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return -1;
	}

	flags = S_IRUSR | S_IWUSR;
	//if ((semid = semget(key, res_num, flags)) == -1) {
	if ((semid = semget(key, 1, flags)) == -1) {
		perror("semget");
		return -1;
	}

	return semid;
}

void close_sem_sysv(int semid)
{
	if (semid > 0) {
		fprintf(stdout, "close semid: %d\n", semid);
		close(semid);
	}
}

int get_sem_sysv(int semid)
{
	struct sembuf semops;

	if (semid < 0) return -2;

	semops.sem_num 	= 0;
	semops.sem_op	= -1;
	semops.sem_flg	= SEM_UNDO;
	if (semop(semid, &semops, 1) == -1) {
		perror("semop");
		return -1;
	}

	return 0;
}

int release_sem_sysv(int semid)
{
	struct sembuf semops;

	if (semid < 0) return -2;

	semops.sem_num 	= 0;
	semops.sem_op	= 1;
	semops.sem_flg	= SEM_UNDO;
	if (semop(semid, &semops, 1) == -1) {
		perror("semop");
		return -1;
	}

	return 0;
}



