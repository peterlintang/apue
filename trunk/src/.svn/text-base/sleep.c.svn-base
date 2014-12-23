#include <signal.h>
#include <unistd.h>

/*alarm process */
static void
sig_alam(int signo)
{
        /*do nothing*/
}

unsigned int
sleep2(unsigned int nsecs)
{
        if (signal(SIGALRM, sig_alam) == SIG_ERR)
        {
                return (nsecs);
        }
        alarm(nsecs);
        pause();
        return(alarm(0));
}

