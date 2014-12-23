#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define 	max(a, b) \
	({ typeof(a) _a_ = a; typeof(b) _b_ = b;\
		_a_ > _b_ ? _a_ : _b_; })
/*
 *## usage and # usage
 */
#define COMMAND(name)  { #name, name##_command }


/*
*offsetof usage
*/
#define offsetof(type, member) __builtin_offsetof (type, member)

/*
*varidic macro
*/
#undef debug
#define debug
#ifdef debug
#define dprintf(format, args...) printf(format, ##args)
#else
#define dprintf(format, args...)  
#endif

/*
*define gcc version
*/
#define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 \
	+ __GNUC_PATCHLEVEL__  )

/*
*usage of waring and error 
*/
#if defined(debug)
#warning "running in debug mode"
#endif
#if !defined(debug)
#error "you run the executable in nondebug mode, please set to debug mode!"
#endif

int quare (int a);
int addquare(int a, int b);
int usecase(char c);

void quit_command(void);
void help_command(void);
static inline int inc(int *a);

char *my_index(char *s, int c);
char *my_rindex(char *s, int c);

/*
 * constructor and destructor
 * will run before the main run,
 * and before exit.
 */
void my_constructor1(void) __attribute__ ((constructor (101)));
void my_destructor1(void) __attribute__ ((destructor (101)));
void my_constructor2(void) __attribute__ ((constructor (102)));
void my_destructor2(void) __attribute__ ((destructor (102)));

void my_constructor1(void)
{
	dprintf("hello we are in constructor 1!\n");
}

void my_destructor1(void)
{
	dprintf("good bye we are in destructor 1!\n");
}

void my_constructor2(void)
{
	dprintf("hello we are in constructor 2!\n");
}

void my_destructor2(void)
{
	dprintf("good bye we are in destructor 2!\n");
}


/*
*deprecated function
*/
void my_deprecated(void) __attribute__((deprecated));

void my_deprecated(void)
{
	printf("we are in deprecated function which will be remove!\n");
}


void quit_command(void)
{
	dprintf("quit command\n");
}

void help_command(void)
{
	dprintf("help command\n");
}

/*
*inline function
*/
static inline int inc (int *a)
{
	dprintf("a value:%d\n", *a);
	return ++(*a);
}

int
main(int argc, char *argv[])
{
	/*
	*local label should be declared at the beginning of the block
	*/
	__label__ failer;

	struct command {
		char *name;
		void (*function)(void);
	};

	struct command commands[] = {
		COMMAND(quit),
		COMMAND(help),
	};
	
	/*
	*test deprecated function
	*/
	my_deprecated();

	volatile int *ptr;
	/*
	*test usage of ## and #
	*/
	int j __attribute__ ((packed)) = 0;
	for (j = 0; j < 2; j++)
		commands[j].function();
	
	dprintf("\ncall inline function inc\n value:%d, %d\n", j, inc(&j));
//	dprintf("inc value:%d\n", inc(&j));	
//	dprintf("after inc: %d\n", j);
	dprintf("special character :\e ....\n");
	dprintf("align of variable j: %d\n", __alignof__(j));

	struct line {
		int length;
		char contents[0];
	};
	
	/*
	*struct with zero length
	*/
	struct line *thisline = (struct line *) \
		malloc (sizeof(struct line) + 100);
	thisline->length = 100;
	for (j = 0; j < thisline->length; j++)
	{
		thisline->contents[j] = j/40 + 30;
	}
	dprintf("length: %d\n string: %s\n", thisline->length, thisline->contents);

	/*
	*variable length arrays
	*/
	char *pendstr(char *s1, char *s2)
	{
		char *str;
		str = malloc(sizeof(char) * (strlen (s1) + strlen (s2)));
		strcpy (str, s1);
		strcpy (str + strlen (s1), s2);
		return str;
	}
	dprintf("pend str1: %s and str2: %s, str: %s\n", "hello", "world", pendstr("hello", "world") );
	
	int d[6] = {[5] = 4, [4] = 6, [1 ... 3] = 1};
	for (j = 0; j < 6; j++)
	{
		dprintf("a[%d]: %d\n", j, d[j]);
	}



	struct foo 
	{
		char x __attribute__((aligned(2)));
		char y __attribute__ ((aligned(8)));
		char z;
	};

	dprintf("struct foo's y offset: %d\n", offsetof(struct foo, y));

	struct foo bar = 
	{
		.x = 1,
		.y = 2,
		.z = 3,
	};
	dprintf("struct foo\n .x = %d\n .y = %d\n .z = %d\n", bar.x, bar.y , bar.z);
	dprintf("struct foo's x offset: %d\n", offsetof(struct foo, x));
	dprintf("struct foo's y offset: %d\n", offsetof(struct foo, y));
	dprintf("struct foo's z offset: %d\n", offsetof(struct foo, z));
	dprintf("sizeof struct foo: %d\n", sizeof(struct foo));
	struct foo car = 
	{
		x: 2,
		y: 3,
		z: 4,
	};
	dprintf("struct foo\n .x = %d\n .y = %d\n .z = %d\n", car.x, car.y , car.z);
	
	/*
	*packed usage
	*/
	struct employer {
		char id;
		int x[2] __attribute__ ((packed));
	};

	struct employer employer = {
		.id   = 2,
		.x[0] = 1,
		.x[1] = 3,
	};
	
	dprintf("sizeof struct employer: %d\n", sizeof(struct employer));
	dprintf("employer id: %d, x.0: %d, x.1: %d\n", employer.id, employer.x[0], employer.x[1]);

	dprintf("touch volatile var pointer \n");
	ptr = &j;
	dprintf("ptr pointer to 's value: %d\n", *ptr);
	*ptr = 50;
	dprintf("ptr pointer to 's value: %d\n", *ptr);

//	float k = 10.0, n = 20.0;
//	asm ("fsinx %1,%0" : "=f" (n) : "f" (k));
//	dprintf("after asm j:%d\n", j);


	char *pter = "hello world nice";
	dprintf("\n\n%s\n", pter);
	
	dprintf("%s length: %d\n", pter, strlen(pter));
	dprintf("my_index function : %s\n", my_index(pter, ' '));
	dprintf("my_rindex function: %s\n", my_rindex(pter, ' '));

	/*
	*usage of special stander macros
	*/
	dprintf("current filename: %s\n", __FILE__);
	dprintf("current line num: %d\n", __LINE__);
	dprintf("current date : %s\n", __DATE__);
	dprintf("current time : %s\n", __TIME__);
	if (__STDC__ == 1)
		dprintf("current stdc : %s\n", "ISO standard C");

	/*
	*gnuc common extensions 
	*/
	dprintf("current counter: %d\n", __COUNTER__);

	dprintf("gcc version: %d\n", GCC_VERSION);
	/*
	 *zero-length in struct
	 */
	struct f {
		int length;
		char str[0];
	};
	
	void *p;
	p = &&failer;
	dprintf("jump to failer\n");
//	goto *p;
	/*
	 *register variable
	 */
	register int tmpreg = 100;
	for (; tmpreg < 100; tmpreg++) 
		printf("tmpreg value: %d\n", tmpreg);

	struct f foo = {.length = 10};
	int a=10, b=20;
	char str[0] __attribute__ ((__unused__));
	typedef _Complex float __attribute__((mode(XC))) _Complex80;
	_Complex int x = 2 + 1i;
	x = ~x;
	dprintf("struct f foo's length=: %d\n", foo.length);
	dprintf("hello world!\n");
	dprintf("complex: real %d, image %d\n", __real__ x, __imag__ x);
	dprintf("int %d, %d max: %d\n", a, b, max(a, b));
	dprintf("%d, %d, %d\n", a, b, a ? : b );	
	dprintf("void size: %d\nfunc size: %d\n", sizeof(void *), sizeof(quare));
	asm ("" : : : "memory");
	int i = 1;

	int quare (int a) 
	{
		printf("access i: %d\n", i);
//		goto failer;  	//test label
		return a * a;
	}
	
//	int fun_quare () __attribute__ ((__weak__, alias ("quare")));

	printf("add %d 's quare is: %d\n", 10, quare(10));
	printf("addquare %d + %d^2: %d\n", 10, 10, addquare(10, 10));
	usecase('d');
	failer:
		dprintf("exit \n");

	exit(0);
} 


int addquare(int a, int b)
{
	/*
 	 *runtime initialize
	 */
	int c = a + b; 
	printf("a + b =: %d\n", c);
	printf("__PRETTY_FUNCTION__=: %s\n", __PRETTY_FUNCTION__);
	return b + quare(a);	
}

int quare (int a) 
{
	char str[a] __attribute__ ((__unused__));//variable-length 
	printf("__func__ name=: %s\n", __func__);
	return a * a;
}



int usecase(char c)
{
	switch (c)
	{
		case 'a' ... 'z':
			printf("%c belongs a...z\n", c);
			break;
		case 'A' ... 'Z':
			printf("%c belongs A...Z\n", c);
	}
	return 0;
}













