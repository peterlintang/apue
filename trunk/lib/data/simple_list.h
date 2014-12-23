/*
 * implements a simple interface of list
 *
 */
#ifndef _simple_list_H
#define _simple_list_H

typedef struct __simple_list_item_t {
	void *value;
	struct __simple_list_item_t *prev;
	struct __simple_list_item_t *next;
} simple_list_item_t;

/* list item interfaces */
simple_list_item_t *_new_simple_list_item(void *value);
void _destroy_simple_list_item(simple_list_item_t **item_ptr);

typedef struct __simple_list_t {
	struct __simple_list_item_t *head;
	struct __simple_list_item_t *tail;
	
	unsigned int count;
} simple_list_t;


/* simple list interfaces */
simple_list_t *_new_simple_list(void);
int _is_empty_simple_list(simple_list_t *list);
int _insert_item_to_simple_list_before(simple_list_t *list, 
					simple_list_item_t *item, 
					simple_list_item_t *before);
int _insert_item_to_simple_list_after(simple_list_t *list, 
					simple_list_item_t *item, 
					simple_list_item_t *after);
simple_list_item_t *_get_simple_list_head(simple_list_t *list);
simple_list_item_t *_get_simple_list_tail(simple_list_t *list);
simple_list_item_t *_next_simple_list_item(simple_list_item_t *item);
simple_list_item_t *_prev_simple_list_item(simple_list_item_t *item);
//void _del_item_from_simple_list(list_t *list, list_item_t *item);
int _del_item_from_simple_list(simple_list_t *list, simple_list_item_t *item);
simple_list_item_t *_search_item_in_simple_list(simple_list_t *list, 
					simple_list_item_t *start,  
					void *value);
simple_list_item_t *_search_item_in_simple_list_reverse(simple_list_t *list, simple_list_item_t *start,  void *value);
void _destroy_simple_list(simple_list_t **list_ptr);


#endif
