#ifndef	__queue_H__
#define __queue_H__

typedef struct __queue_item_t {

	void 	*data;
	struct  __queue_item_t *next;

} queue_item_t;

queue_item_t *new_queue_item(void *data);
void	destroy_queue_item(queue_item_t **pnode, int force);

typedef struct __queue_t {

	char	*name;			/* for future extended */
	unsigned int	id;		/* for future extended */
	struct __queue_t *next;		/* for future extended */

	unsigned int	count;
	struct __queue_item_t *head;

} queue_t;

queue_t *new_queue(char *name, unsigned int id);
void destroy_queue(queue_t **pqueue);
void *put_queue_tail(queue_t *queue, void *data);
void *get_queue_head(queue_t *queue);
int  is_empty_queue(queue_t *queue);

#endif
