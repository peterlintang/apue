/*
 * implement the simple queue type
 * only support create destroy put get functions
 */

#ifndef _simple_queue_H
#define _simple_queue_H

typedef struct __simple_queue_t {
	void *data;
	struct __simple_queue_t *next;
} simple_queue_t;

typedef struct __simple_queue_head {
//	unsigned int count;
	simple_queue_t *first;
//	struct __queue_t *head;
} simple_queue_head;

/* 
 * will free @item->data
 */
void _destroy_simple_queue_item(simple_queue_t *item);

/* 
 * will not free @item->data
 */
void _destroy_simple_queue_item_without_data(simple_queue_t *item);

/* queue interfaces */
simple_queue_head *_new_simple_queue(void);

void _destroy_simple_queue(simple_queue_head **head);

int _put_item_to_simple_queue(simple_queue_head *head, void *in);

void *_get_item_from_simple_queue(simple_queue_head *head);

int _is_empty_simple_queue(simple_queue_head *head);


void _destroy_simple_queue_without_data(simple_queue_head **head);

#endif /* _simple_queue_H */
