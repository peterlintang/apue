
#include <stdio.h>	/* for stdin stdout stderr */
#include <stdlib.h> 	/* for free calloc */
#include "simple_stack.h"

simple_stack_head *_new_simple_stack(void)
{
	simple_stack_head *head = calloc(1, sizeof(simple_stack_head));
	return head;
}

/*
 * put an element to the stack
 * return value: 1 success
 *		 0 fail
 * 		 -1 error
 */
int _put_to_simple_stack(simple_stack_head *head, void *in)
{
	simple_stack_t *item = NULL;

	if (!head) {
//		fprintf(stderr, "%s : parameters error\n", __func__);
		return 0;
	}
	
	if (!(item = calloc(1, sizeof(simple_stack_t)))) {
//		fprintf(stderr, "%s : cannot alloc memory for new item\n",
//				__func__);
		return -1;
	}

	item->data = in;
	item->next = head->items;
	head->items = item;

	return 1;
}

/*
 * the caller should later free the memory pointed by @data
 * the return value.
 */
void *_get_from_simple_stack(simple_stack_head *head)
{
	void *data = NULL;

	if (head && head->items) {
		simple_stack_t *item = head->items;
		data = item->data; 
		head->items =item->next;
		free(item);
	}

	return data;
}

/*
 * judge the stack is empty or not
 * return value: 1 yes
 *		 0 no
 * 		 -1 error
 */
int _is_empty_simple_stack(simple_stack_head *head)
{
	if (!head) {
//		fprintf(stderr, "%s : parameters error\n", __func__);
		return -1;
	}

	if (head->items)
		return 0;
	else 
		return 1;
}

void _destroy_simple_stack_item(simple_stack_t *item)
{
	if (item) {
		if (item->next) _destroy_simple_stack_item(item->next);
		free(item->data);
		free(item);
	}
}

void _destroy_simple_stack(simple_stack_head **head_ptr)
{
	if (head_ptr && *head_ptr) {
		if ((*head_ptr)->items)
			_destroy_simple_stack_item((*head_ptr)->items);
		free((*head_ptr));
		*head_ptr = NULL;
	}
}

/* 
 * these are the extended functions
 */
void _destroy_simple_stack_item_without_data(simple_stack_t *item)
{
	if (item) {
		if (item->next) _destroy_simple_stack_item_without_data(item->next);
		free(item);
	}
}

void _destroy_without_data_simple_stack(simple_stack_head **head_ptr)
{
	if (head_ptr && *head_ptr) {
		if ((*head_ptr)->items)
			_destroy_simple_stack_item_without_data((*head_ptr)->items);
		free((*head_ptr));
		*head_ptr = NULL;
	}
}

