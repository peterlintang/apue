#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*if u want to debug mode, define DEBUG; else undefine DEBUG*/
#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout,fmt, ##args)
#else
#define dprintf(fmt, args...) 
#endif

/*more safe macro*/
#define maxint(a, b) ({int _a = (a); int _b = (b); _a > _b ? _a : _b;})
#define minint(a, b) ({int _a = (a); int _b = (b); _a > _b ? _b : _a;})

/*use of typeof*/
#define max(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define min(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _b : _a; })

int foo(int x)
{
	return 4 * x + x * x;
}

int 
main(int argc, char *argv[])
{
	/*compound statments*/
	int z = ({ int y = foo(4); int z;
	   if (y > 0) z = y;
	   else z = -y;
	   z;});
	dprintf("%d\n", z);

	/*more safe macro*/
	dprintf("%d min %d\n", minint(4, 5), maxint(4, 5));

	/*local labels: which should come at the beginning of the block*/
	do {
		__label__ found;
		int i;
		for (i = 0; i < 10; i++)
		{
			if (i == 4)
			{
				goto found;
			}
		}
		found:
			dprintf("found: %d\n", i);
	} while (0);

	/*use label as values*/
	do {
		__label__ found1;
		void *ptr;
		ptr = &&found1;
		goto *ptr;
		dprintf("should be here\n");
		found1:
			dprintf("found\nlabel addrs: %0x\n", (int) ptr);
	} while (0);

	/*use of typeof*/
	dprintf("typeof\n%d max %d\n", max(5, 4), min(4, 5));
	dprintf("typeof\n%lf max %lf\n", max(5.4, 4.5), min(4.5, 5.4));

	/*use of condition with omitted operands*/
	int j = 4;
	dprintf("conditionals omitted\n%d\n", j++ ? : 4);
	j = 4;
	dprintf("conditionals omitted\n%d\n", j++ ? j : 4);

	exit(0);
}




