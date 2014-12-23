/*
 *
 * handle list
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "list.h"	/* our own head file */

/*
 * list item
 */
list_item_t *_new_list_item(void *value)
{
	list_item_t *node;

	node = (list_item_t *)calloc(1, sizeof(list_item_t));
	if (node) {
		node->value = value;
	}
	return node;
}

/*
static void _destroy_list_item(list_item_t **itemPtr)
{
	if (itemPtr && *itemPtr) {
		free(*itemPtr);
		*itemPtr = NULL;
	}
}
*/

void _destroy_list_item(list_item_t **itemPtr)
{
	if (itemPtr) {
		list_item_t *item = *itemPtr;
		if (item) {
			/* NOTE: DOES NOTE FREE VALUE! */
			free(item);
			*itemPtr = NULL;
		}
	}
}

/*
 * list 
 *
 *
 */

list_t *_new_list(void)
{
	list_t *list;

	list = (list_t *)calloc(1, sizeof(list_t));
	if (list) 
		pthread_mutex_init(&list->lock);
	return list;
}

list_item_t *
_insertAfter(list_t *list, list_item_t *new, list_item_t *after)
{
	if (new) {
		pthread_mutex_lock(&list->lock);
		after = after ? after : list->tail;
		if (after) {
			new->next = after->next;
			new->prev = after;
			after->next = new;
			if (new->next)
				new->next->prev = new;
			else
				list->tail = new;
		} else {
			list->head = list->tail = new;
		}
		list->count++;
		pthread_mutex_unlock(&list->lock);
	}
	return new;
}

list_item_t *
_insertBefore(list_t *list, list_item_t *new, list_item_t *before)
{
	if (new) {
		pthread_mutex_lock(&list->lock);
		before = before ? before : list->head;
		if (before) {
			new->next = before;
			new->prev = before->prev;
			before->prev = new;
			if (new->prev)
				new->prev->next = new;
			else
				list->head = new;
		} else {
			list->head = list->tail = new;
		}
		list->count++;
		pthread_mutex_unlock(&list->lock);
	}
	return new;
}

list_item_t *
_remove(list_t *list, list_item_t *old)
{
	if (old) {
		pthread_mutex_lock(&list->lock);
		if (old->prev)
			old->prev->next = old->next;
		else
			list->head = old->next;

		if (old->next)
			old->next->prev = old->prev;
		else
			list->tail = old->prev;

		list->count--;
		pthread_mutex_unlock(&list->lock);
	}
	return old;
} 

inline list_item_t *_pop(list_t *list)
{
	return _remove(list, list->head);
}

inline list_item_t *_drop(list_t *list)
{
	return _remove(list, list->tail);
}

inline unsigned int _count(list_t *list)
{
		return list->count;
}

inline list_item_t * _first(list_t *list)
{
	return list->head;
}

inline list_item_t *_last(list_t *list)
{
	return list->tail;
}

inline list_item_t *_next(list_item_t *item)
{
	if (item)
		return item->next;
	return NULL;
}

inline list_item_t *_prev(list_item_t *item)
{
	if (item)
		return item->prev;
	return NULL;
}

list_item_t *
_search_list(list_t *list, 
		list_item_t *start, 
		const char *value)
{
	if (value) {
		unsigned int len = strlen(value);
		start = start ? start : list->head;
		while (start) {
			if ((strlen(start->value) == len) 
				&& !strcmp(value, start->value))
				break;
			start = start->next;
		}
	} else {
		return NULL;
	}
	return start;
}

/*
list_item_t *
_find_item_by_name(list_t *list, 
			list_item_t *start, 
			const char *name)
{
	if (name) {
		unsigned int len = strlen(name);
		start = start ? start : list->head;
		while (start) {
			if ((strlen(start->name) == len) 
				&& !strcmp(name, start->name))
				break;
			start = start->next;
		}
	} else {
		return NULL;
	}
	return start;
}
*/

list_item_t *
_find_item_by_value(list_t *list, 
			list_item_t *start, 
			const char *value)
{
	if (value) {
		unsigned int len = strlen(value);
		start = start ? start : list->head;
		while (start) {
			if ((strlen(start->value) == len) 
				&& !strcmp(value, start->value))
				break;
			start = start->next;
		}
	} else {
		return NULL;
	}
	return start;
}

/*
list_item_t *
_search_list_reverse(list_t *list, 
			list_item_t *start, 
			const char *name)
{
	if (name) {
		unsigned int len = strlen(name);
		start = start ? start : list->tail;
		while (start) {
			if ((strlen(start->name) == len) 
				&& !strcmp(name, start->name)) 
				break;
			start = start->prev;
		}
	} else {
		return NULL;
	}
	return start;
}
*/

/*
list_item_t *
_find_item_by_name_reverse(list_t *list, 
				list_item_t *start, 
				const char *name)
{
	if (name) {
		unsigned int len = strlen(name);
		start = start ? start : list->tail;
		while (start) {
			if ((strlen(start->name) == len) 
				&& !strcmp(name, start->name))
				break;
			start = start->prev;
		}
	} else {
		return NULL;
	}
	return start;
}
*/

list_item_t *
_find_item_by_value_reverse(list_t *list,
				list_item_t *start,
				const char *value)
{
	if (value) {
		unsigned int len = strlen(value);
		start = start ? start : list->tail;

		while (start) {
			if ((strlen(start->value) == len) 
				&& !strcmp(value, start->value))
				break;
			start = start->prev;
		}
	} else {
		return NULL;
	}
	return start;
}

void _destroy_list(list_t **listPtr)
{
	if (listPtr && *listPtr) {
		if (_count(*listPtr) > 0) {
			list_item_t *item;
			while ((item = _pop(*listPtr)) != NULL)
				_destroy_list_item(&item);
		}
		pthread_mutex_destroy(&(*listPtr)->lock);
		free(*listPtr);
		*listPtr = NULL;
	}
}
