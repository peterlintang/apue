
#include <stdlib.h>	/* for calloc & free */
#include <string.h>	/* for strdup */
#include "queue.h"

/* queue item interfaces */
queue_item_t *new_queue_item(void *data)
{
	queue_item_t *node = NULL;
	if (data) {
		node = (queue_item_t *)calloc(1, sizeof(*node));
		if (node) node->data = data;
	}
	return node;
}

void destroy_queue_item(queue_item_t **pnode, int force)
{
	queue_item_t *node = NULL;
	if (pnode && *pnode) {
		node = *pnode;
		if (force && node->data) free(node->data);
		free(node);
		*pnode = NULL;
	}
}



/* queue interfaces */
queue_t *new_queue(char *name, unsigned int id)
{
	queue_t *queue = NULL;

	name = name ? name : "queue";

	queue = calloc(1, sizeof(*queue));
	if (queue) {
		queue->name = strdup(name);
		queue->id   = id;
	}
	return queue;
}

void destroy_queue(queue_t **pqueue)
{
	void	     *data  = NULL;
	queue_item_t *node  = NULL;
	queue_t      *queue = NULL;

	if (pqueue && *pqueue) {
		queue = *pqueue;
		while ((data = get_queue_head(queue)) != NULL) {
			free(data);
		}
		free(queue);
		*pqueue = NULL;
	}
}

void *put_queue_tail(queue_t *queue, void *data)
{
	queue_item_t *last = NULL;
	queue_item_t *node = NULL;

	if (!queue || !data) return NULL;

	node = new_queue_item(data);
	if (!node) {
		return NULL;
	}

	last = queue->head;
	if (!last) {
		queue->head = node;
	} else {
		while (last->next) last = last->next;
		last->next = node;
	}

	queue->count++;

	return data;
}

void *get_queue_head(queue_t *queue)
{
	void	     *data = NULL;
	queue_item_t *node = NULL;

	if (!queue || !queue->head) return NULL;

	node = queue->head;
	queue->head = node->next;
	
	data = node->data;

	destroy_queue_item(&node, 0);

	queue->count--;

	return data;
}

int is_empty_queue(queue_t *queue)
{
	if (queue) return queue->count ? 1 : 0;
	return -1;
}
