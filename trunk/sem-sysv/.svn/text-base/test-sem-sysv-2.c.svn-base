
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEM_SYSV_PATH "./hello-test"
#define SEM_SYSV_ID	0

int main(int argc, char *argv[])
{
	int	ret = 0;
	int	semid = -1;

	semid = open_sem_sysv(SEM_SYSV_PATH, SEM_SYSV_ID);
	if (semid < 0) {
		exit(2);
	}

	get_sem_sysv(semid);
	fprintf(stdout, "sleep\n");
	sleep(1);
	release_sem_sysv(semid);
	
	close_sem_sysv(semid);

	return ret;
}
