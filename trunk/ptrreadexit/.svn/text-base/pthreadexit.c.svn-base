#include "apue.h"
#include <pthread.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

struct foo {
	int a, b, c, d;
};

void 
printfoo(const char *s, const struct foo *fp)
{
	printf(s);
	printf(" structure at 0x%x\n", (unsigned )fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *
thr_fn1(void *arg)
{
	struct foo foo = {1, 2, 3, 4};
//	printf("thread 1 returning\n");
	printfoo("thread 1:\n", &foo);
	return ((void *)&foo);
}

void *
thr_fn2(void *arg)
{
//	printf("thread 2 exiting\n");
	printf("thread 2: ID is %d\n", (unsigned int )pthread_self());
	pthread_exit((void *) 0);
}

int 
main(int argc, char *argv[])
{
	int 		err;
	pthread_t	tid1, tid2;
//	void		*tret;
	struct foo	*fp;

/*
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		printf("can't create thread1\n");
		exit(1);
	}
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		printf("can't create thread2\n");
		exit(1);
	}
	printf("thread 1 exit code %d\n", (int )tret);
	err = pthread_join(tid1, &tret);
	if (err != 0)
	{
		printf("can't join with thread 1: %s\n", strerror(err));
		exit(1);
	}
	err = pthread_join(tid2, &tret);
	if (err != 0)
	{
		printf("can't join with thread 2: %s\n", strerror(err));
		exit(1);
	}
	printf("thread 2 exit code %d\n", (int )tret);
*/
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err)
	{
		printf("can't create thread 1: %s\n", strerror(err));
		exit(1);
	}
	err = pthread_join(tid1, (void *)&fp);
	if (err)
	{
		printf("can't join with thread 1: %s\n", strerror(err));
		exit(1);
	}
	sleep(1);

	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err)
	{
		printf("can't create thread 2: %s\n", strerror(err));
		exit(1);
	}
	printfoo("parent:\n", fp);

	exit(0);

}
