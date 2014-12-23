
#include <stdio.h>
#include <string.h>
#include "simple_queue.h"

int main(int argc, char *argv[])
{
	char *ptr = NULL;
	char buf[64];
	char buf2[64];
	simple_queue_head *head = _new_simple_queue();
	if (!head) 
		return 0;
	
	strcpy(buf, "hello world");
	if (_put_item_to_simple_queue(head, (void *)buf))
		fprintf(stdout, "put OK\n");

	strcpy(buf2, "hello john");
	if (_put_item_to_simple_queue(head, (void *)buf2))
		fprintf(stdout, "put OK\n");

	ptr = _get_item_from_simple_queue(head);
	if (ptr) 
		fprintf(stdout, "get OK. data: %s\n", (char *)ptr);

	ptr = _get_item_from_simple_queue(head);
	if (ptr) 
		fprintf(stdout, "get OK. data: %s\n", (char *)ptr);

	if (_is_empty_simple_queue(head))
		fprintf(stdout, "empty queue\n");
	
	fprintf(stdout, "head address : %p\n", head);
	_destroy_simple_queue(&head);
	fprintf(stdout, "head address : %p\n", head);
	return 0;
}






