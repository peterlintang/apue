
#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

typedef struct __list_node_t {
	void *data;

	unsigned char status;
#define STATUS_INUSE	2	/* for future use */
#define STATUS_REMOVED	1
//#define STATUS_NORMAL	0

	struct __list_node_t *prev;
	struct __list_node_t *next;
} list_node_t;

list_node_t *new_list_node(void *data);
void destroy_list_node(list_node_t **ppnode);

typedef struct __list_head {
	int	count;
	struct list_node_t *head;

	pthread_mutex_t	lock;	// if has pthread_mutex support 
} list_head;

list_head *new_list(void);
void destroy_list(list_head **pplist);

list_node_t *insert_node_after(list_head *list, list_node_t *new, list_node_t *after);
list_node_t *insert_node_before(list_head *list, list_node_t *new, list_node_t *before);

list_head *list_reverse(list_head *list);

int list_count(list_head *list);
int list_is_empty(list_head *list);

static int node_in_list(list_head *list, list_node_t *node);
list_node_t *remove_node(list_head *list, list_node_t *old);

list_node_t *pop(list_head *list);
list_node_t *drop(list_head *list);
list_node_t *first(list_head *list);
list_node_t *last(list_head *list);
list_node_t *next(list_node_t *node);
list_node_t *prev(list_node_t *node);



#endif // SIMPLE_LIST_H
