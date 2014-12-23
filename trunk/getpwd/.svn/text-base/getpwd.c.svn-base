#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

#define NOSIGHT 0x1fU


void my_exit_1(void)
{
	printf("exit 1 from getpwd\n");
}

void my_exit_2(void)
{
	printf("exit 2 from getpwd\n");
}

int 
main(int argc, char *argv[])
{
	char   *tmp; 
	struct passwd *mypasswd;
	pid_t 	pid;

	atexit(my_exit_1);	
	atexit(my_exit_2);	

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error!\n");
	}
	else if (pid == 0)
	{
		fprintf(stdout, "print from child\n");
	}
	else
	{
		sleep(2);
		fprintf(stdout, "waiting for child to finish\n");
		sleep(2);
		waitpid(pid, NULL, 0);	
		fprintf(stdout, "print from parent\n");
//		sleep(10);
	}

	setpwent();
	while ((mypasswd = getpwent()) != NULL)
	{	
		printf("name: %s\n", mypasswd->pw_name);
		printf("passwd: %s\n", mypasswd->pw_passwd);
		printf("uid: %d\tgid: %d\n", mypasswd->pw_uid, mypasswd->pw_gid);
		printf("home dir: %s\n", mypasswd->pw_dir);
		printf("shell: %s\n\n", mypasswd->pw_shell);
	}

	tmp = getenv("HOME");
	if (!tmp)
		printf("HOME not export\n");
	else
		printf("HOME: %s\n", tmp);

	tmp = getenv("HOME");
	if (!tmp)
		printf("srcs not export\n");
	else
		printf("srcs: %s\n", tmp);

	sprintf(tmp, "/home");
	printf("tmp:%s\n", tmp);

	if((setenv("HOME", tmp, 1)) == -1)
		printf("set srcs error\n");
	else
		printf("set srcs ok\n");

	tmp = getenv("HOME");
	if (!tmp)
		printf("srcs not export\n");
	else
		printf("srcs: %s\n", tmp);
	
	printf("parent pid: %d\n", getppid());
	printf("pid       : %d\n", getpid());
	printf("%0x\n", NOSIGHT);

//	_exit(0);

	exit(0);
}




