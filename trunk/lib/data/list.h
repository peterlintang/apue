#ifndef	LIST_H
#define LIST_H


typedef struct __list_item_t {
//	char	*name;
	void	*value;
	struct __list_item_t	*prev;
	struct __list_item_t 	*next;
} list_item_t;

typedef struct __list_t {
	struct __list_item_t 	*head;
	struct __list_item_t 	*tail;

	unsigned int	   	count;

	pthread_mutex_t		lock;
} list_t;



/* list item interfaces */
list_item_t *_new_list_item(void *value);

void _destroy_list_item(list_item_t **);

/* list interfaces */
list_t *_new_list(void);

list_item_t *
_insertAfter(list_t *list, 
		list_item_t *new, 
		list_item_t *after);

list_item_t *
_insertBefore(list_t *list, 
		list_item_t *new, 
		list_item_t *before);

list_item_t *_remove(list_t *list, list_item_t *old);

/* inline function */
list_item_t *_pop(list_t *list);

list_item_t *_drop(list_t *list);

unsigned int _count(list_t *list);

list_item_t *_first(list_t *list);

list_item_t *_last(list_t *list);

list_item_t *_next(list_item_t *item);

list_item_t *_prev(list_item_t *item);
/***/

list_item_t *
_search_list(list_t *list, 
		list_item_t *start, 
		const char *value);

/*
list_item_t *
_search_list(list_t *list, 
		list_item_t *start, 
		const char *name);
*/

/*
list_item_t *
_find_item_by_name(list_t *list, 
			list_item_t *start, 
			const char *name);
*/

list_item_t *
_find_item_by_value(list_t *list, 
			list_item_t *start, 
			const char *value);

/*
list_item_t *
_search_list_reverse(list_t *list, 
			list_item_t *start, 
			const char *name);
*/

/*
list_item_t *
_find_item_by_name_reverse(list_t *list, 
				list_item_t *start, 
				const char *name);
*/

list_item_t *
_find_item_by_value_reverse(list_t *list, 
				list_item_t *start, 
				const char *value);
void _destroy_list(list_t **);

#endif /* LIST_H */
