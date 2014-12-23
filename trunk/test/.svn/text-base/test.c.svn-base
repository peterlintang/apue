#include "apue.h"

#define BUFSIZE 1024
#define test (-0UL)

#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

int 
main (int argc, char *argv[])
{
	int n;
        char buff[BUFSIZE];

        while ((n = read(STDIN_FILENO, buff, BUFSIZE)) > 0)
        {
                if (write(STDOUT_FILENO, buff, n) != n)
                {
                        errprintf("write error\n");
                }
        }

        if (n < 0)
                errprintf("read error\n");
	fprintf(stderr, "test: %0lx\n", test);

        exit(0);
}

/*
int main(int argc, char *argv[])
{
        int     i = 12;
        char    buf[64];
        char    *p = buf;

//       * 
//       * equal to below
//       * char s[]="0123456789"
//       * *p = s[val % 10];
//       *
        *p = "0123456789"[i % 10];


        fprintf(stdout, "p -> %c\n", *p);

        return 0;
}
*/
         
/*
        while (i != 0) {
                *--p = "0123456789"[i % 10];
                i /= 10;
        }

        fprintf(stdout, "buf end address: %p, p address: %p\n", &buf[64], p);
        //fprintf(stdout, "p -> %c\n", *p);
        for (i = 0; i < 64; i++)
                fprintf(stdout, "i: %d\t %c\n", i, buf[i]);

        return 0;
*/



