
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "share-mem.h"

#define PATHNAME	"./Makefile"
#define SHM_ID		0
//#define SHMFLAGS	(IPC_CREAT | SHM_R | SHM_W)
#define SHMFLAGS	(IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)
//#define SHMFLAGS	(IPC_CREAT | SHM_R | SHM_W)
#define SHMFLAGS2	(SHM_W | SHM_R)

int main(int argc, char *argv)
{
	int 	ret = 0;
	char	buf[256];
	char	buf2[2560];
	void 	*shm = NULL;

	if (!(shm = create_shared_mem(PATHNAME, SHM_ID, 1024,
			SHMFLAGS, NULL, SHMFLAGS2))) {
		fprintf(stderr, "can not creat shared mem: %p\n", shm);
		return -1;
	}

	memset(buf, 'a', 255);
	memset(buf2, 'c', 2550);
	ret = write_shared_mem(shm, buf, 255);
	//fprintf(stdout, "write %d bytes\n", ret);
	ret = write_shared_mem(shm, buf, 255);
	//fprintf(stdout, "write %d bytes\n", ret);
	ret = write_shared_mem(shm, buf, 255);
/*
	ret = write_shared_mem(shm, buf, 255);
	ret = write_shared_mem(shm, buf, 255);
*/
	sleep(10);
	fprintf(stdout, "going to read from shared memory\n");
	ret = read_shared_mem(shm, buf2, strlen(buf2));
	buf2[ret + 1] = '\0';
	fprintf(stdout, "read %d bytes\n", ret);
	fprintf(stdout, "%s\n", buf2);
	sleep(10);

	destroy_shared_mem(&shm);
	return 0;
}
