/*
 * this implements simple interfaces of statck.
 * 1. create a new stack
 * 2. add an item to the stack
 * 3. get an item from the stack
 * 4. jugde an empty stack
 * 5. destroy a stack
 */

#ifndef _simple_stack_H
#define _simple_stack_H

typedef struct __simple_stack_t {
	void *data;
	struct __simple_stack_t *next;
} simple_stack_t;

typedef struct __simple_stack_head {
	struct __simple_stack_t *items;
} simple_stack_head;

/* free @item->data too */
void _destroy_simple_satck_item(simple_stack_t *item);

/* 
 * these are the extended functions, which will no free @item->data
 */
void _destroy_simple_stack_item_without_data(simple_stack_t *item);

/* stack interfaces */
//static stack_head *_new_stack(void);
simple_stack_head *_new_simple_stack(void);
int _put_to_simple_stack(simple_stack_head *head, void *in);
void *_get_from_simple_stack(simple_stack_head *head);
int _is_empty_simple_stack(simple_stack_head *head);
void _destroy_simple_stack(simple_stack_head **head);
void _destroy_without_data_simple_stack(simple_stack_head **head_ptr);

#endif
