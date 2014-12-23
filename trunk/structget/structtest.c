#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int base;
	int data;
	} test, *ptest; 

int 
main(int argc, char *argv[])
{
	int i;
	test *ptr;
	ptest tmp;
	
	ptr=(test *)malloc(sizeof(test));
	printf("base: %x\ndata: %x\n", ptr->base, ptr->data);
	ptr->base=0x1000000; 
	ptr->data=0x2000000;
	printf("base: %x\ndata: %x\n", ptr->base, ptr->data);
	exit(0);
}

