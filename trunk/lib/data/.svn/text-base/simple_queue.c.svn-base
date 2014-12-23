/*
 * this implements the queue interfaces, which only support 
 * 1. create a new queue,
 * 2. add a new item to the end of the queue,
 * 3. get a item from the head of the queue,
 * 4. jugde a queue if empty or not,
 * 5. destroy the queue,
 */

#include <stdio.h>	/* for stdin stdout stderr */
#include <stdlib.h>	
#include <string.h> 	/* for strdup */
#include "simple_queue.h"

simple_queue_head *_new_simple_queue(void)
{
	simple_queue_head *head = calloc(1, sizeof(simple_queue_head));
//	if (!head)
//		fprintf(stderr, "cannot alloc memeory for queue head\n");
	return head;
}

/*
 * put an element to queue.
 * return value 1 success
 *		0 fail
 *		-1 error
 *
 */
int _put_item_to_simple_queue(simple_queue_head *head, void *in)
{
	simple_queue_t *new = NULL;
	simple_queue_t *last = NULL;

	if (!head) {
//		fprintf(stderr, "parameters erro: NULL ptr\n");
		return 0;
	}
	
	if (!(new = calloc(1, sizeof(simple_queue_t)))) {
//		fprintf(stderr, "cannot alloc memeory for new item\n");
		return -1;
	}

	new->data = in;
//	head->count++;

	if (head->first) {
		last = head->first;
		while (last->next) last = last->next;
		last->next = new;
	} else {
//		new->next = head->first;
		head->first = new;
	}

	return 1;
}

void *_get_item_from_simple_queue(simple_queue_head *head)
{
	void *data = NULL;
	if (head) {
		simple_queue_t *item = head->first;
		if (item) {
			head->first = item->next;
			data = item->data;
			free(item);
		}
	}
	return data;
}

/*
 * decide a queue is empty or not
 * return value 1 yes
 *		0 no
 *		-1 error
 */
int _is_empty_simple_queue(simple_queue_head *head)
{
	if (!head) {
		return -1;
	}

	if (head->first) {
		return 0;
	} else {
		return 1;
	}
}

void _destroy_simple_queue_item(simple_queue_t *item)
{
	if (item && item->next) 
		_destroy_simple_queue_item(item->next);
	free(item->data);
	free(item);
}

void _destroy_simple_queue(simple_queue_head **head_ptr)
{
	if (head_ptr && *head_ptr) {
		if ((*head_ptr)->first)
			_destroy_simple_queue_item((*head_ptr)->first);
		free((*head_ptr));
		*head_ptr = NULL;
	}
}

void _destroy_simple_queue_item_without_data(simple_queue_t *item)
{
	if (item && item->next)
		_destroy_simple_queue_item_without_data(item->next);
	free(item);
}

void _destroy_simple_queue_without_data(simple_queue_head **head_ptr)
{
	if (head_ptr && *head_ptr) {
		if ((*head_ptr)->first)
			_destroy_simple_queue_item_without_data((*head_ptr)->first);
		free((*head_ptr));
		*head_ptr = NULL;
	}
}

