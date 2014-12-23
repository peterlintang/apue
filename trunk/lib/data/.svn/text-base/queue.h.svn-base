/*
 * this inplement the interface of 
 * queue.
 */
#ifndef __queue_H
#define __queue_H

#include <stdint.h>		/* for uintX_t */

#define QUEUE_CHUNK_SIZE 	8	/* default chunk size */
#define QUEUE_MAX_CHUNKS	255
#define DEFAULT_QUEUE_TIMEOUT   100

typedef struct __queue_item {
	void *node;
	struct __queue_item *next;
} queue_item_t;

typedef struct __cqueue_t {
	/* configurable vars, but now it is not used */
	uint8_t	status 	 :3;		/* */
	uint8_t blocking :1;		/* block(on) or unblock(off) */
	uint8_t rsv	 :4;		/* not used */
	
	int	disabled;	/* if disable, set; prevents put (allows get, drop) */
	
	uint32_t  chunk_size;		/* configured chunk size, add chunk_size items once time */
	unsigned char max_chunks;	/* configured max num chunks, will never greater than QUEUE_MAX_CHUNKS */ 
	uint32_t  timeout;		/* get timeout if blocking */

	unsigned char num_chunks;	/* next empty point in chunks, should not larger than QUEUE_MAX_CHUNKS */
	queue_item_t *chunks[QUEUE_MAX_CHUNKS];

	/* pthread safe controls */
	pthread_mutex_t lock;
	pthread_cond_t	wait;

	/* queue get / put access */
	queue_item_t *putpos;
	queue_item_t *getpos;

	uint32_t pending;	/* num of pending items */
	uint32_t drops;		/* num of pending items */
} cqueue_t;

/* queue interfaces */
int _grow_cqueue(cqueue_t *q);

void _shrink_cqueue(cqueue_t *q);

cqueue_t *_new_cqueue(uint32_t chunk_size, unsigned char max_chunks);

int _put_cqueue(cqueue_t *cqueue, void *in);

void __get_data_timeout_block(cqueue_t *q, void **data);

void *_get_cqueue(cqueue_t *cqueue);

void *_drop_cqueue(cqueue_t *cqueue);

void _set_blocking_cqueue(cqueue_t *queue, int toggle);

void _set_timeout_cqueue(cqueue_t *queue, uint32_t timeout_ms);

void _disable_cqueue(cqueue_t *queue);

void _destroy_cqueue(cqueue_t **cqueue_ptr);

#endif	/* __queue_H */
