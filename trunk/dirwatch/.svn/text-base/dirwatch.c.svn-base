#define _GNU_SOURCE	/* needed to get the defines */
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int fd;
	char *name;
    int active;
} list_t;

static volatile int event_fd;
static int max_list;
static list_t *fdlist;

static void handler(int sig, siginfo_t *si, void *data)
{
	event_fd = si->si_fd;
}

static void sig_chld(int sig){
	waitpid(-1, NULL, WNOHANG);
}

void watch(const char *dir, const char *name){
	int i, fd = 0;
	
	printf("Watching %s (%s)... ", dir, name);
    if ((fd = open(dir, O_RDONLY)) != -1 &&
        fcntl(fd, F_SETSIG, SIGRTMIN + 1) != -1 &&
        fcntl(fd, F_NOTIFY, DN_MODIFY|DN_CREATE|DN_DELETE|DN_MULTISHOT) != -1) {
        
        i=max_list++;
        fdlist = realloc(fdlist, sizeof(list_t)*max_list);
        fdlist[i].fd=fd;
        fdlist[i].name = strdup(name);
        fdlist[i].active = 0;
        
        printf ("[OK]\n");
    } else {
		printf("fd: %d\n", fd);
		perror("not know");
		printf("[Failed] -- either %s doesn't exist or check kernel support for F_NOTIFY!\n",dir);
    }
}

/* 
 * // file descriptors ?
 * close(0); close(1); close(2);
 * open("/dev/null", O_RDWR);
 * dup(0); dup(0);
 */

void do_action(list_t *entry){
    char *cmd_args[] = { "-HUP", NULL, NULL };
    const char *name = entry->name;
    int pid = fork ();
	if (pid == 0){
        // child process
        if (name[0] == '!') {
            printf ("issuing %s\n", (const char *) &name[1]);
            execlp (&name[1],basename (&name[1]), (char *)0);
            if (errno == ENOEXEC) {
                execlp("/bin/ash","ash","-c", (const char *) &name[1], (char *) 0);
            }
        } else {
            cmd_args[1] = (char *) name;
            printf ("issuing HUP to %s\n",name);
            execv ("/usr/bin/killall",cmd_args);
        }
        perror (name);
		exit(1);
	} else {
        int status;
        // parent process
        waitpid (pid,&status,0);
        printf ("[OK]\n");
    }
}

void changed(int fd){
	int i;

	printf("changed... ");
	for (i=0; i<max_list; i++){
		if (fd == fdlist[i].fd){
			printf("%s... ", fdlist[i].name);
			do_action(&fdlist[i]);
			break;
		}
	}
}

int main(void)
{
	struct sigaction act;
	char *line = NULL, *delim;
	size_t size = 0;
	
	// setup signal handlers
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN + 1, &act, NULL);
	signal(SIGCHLD, &sig_chld);
	
	// config
	max_list=0;
	fdlist=NULL;
	while (getline(&line, &size, stdin) > 0){
		if (line[0] == '#') continue;
		delim = index(line,'\n');
		if (delim) *delim = 0; // get rid of newline
		delim = index(line, ' ');
		if (!delim) {
			printf("error parsing input\n");
			return 1;
		}
		*delim=0;
		watch(delim + 1, line);
	}
	
	while (1) {
		pause();
		printf("Got an event on %i\n", event_fd);
		changed(event_fd);
	}
}
