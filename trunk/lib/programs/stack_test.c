
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_stack.h"

int main(int argc, char *argv[])
{
	char *ptr = NULL;
	char *buf = malloc(40 * sizeof(char));
	simple_stack_head *head = _new_simple_stack();
	if (!buf || !head) {
		free(buf);
		_destroy_simple_stack(&head);
		return 0;
	}

	strcpy(buf, "hello world");
	if (_put_to_simple_stack(head, (void *)buf))
		fprintf(stdout, "put to stack OK\n");

	if (_is_empty_simple_stack(head) == 1)
		fprintf(stdout, "empty stack\n");

	/* the caller must free the memory pointed by the value which is returned by _get_from_stack */
	ptr = _get_from_simple_stack(head);
	if (ptr) {
		fprintf(stdout, "get from stack OK. data : %s\n", ptr);
		free(ptr);
	}

	if (_is_empty_simple_stack(head) == 1)
		fprintf(stdout, "empty stack 1\n");
	_destroy_simple_stack(&head);

	fprintf(stdout, "data : %s\n", buf);

	if (_is_empty_simple_stack(head) == 1)
		fprintf(stdout, "empty stack 2\n");
	fprintf(stdout, "head address : %p\n", head);
	
	return 0;
}
