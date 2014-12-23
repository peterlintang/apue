/*
 *
 * implements a simple list interface
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simple_list.h"

simple_list_item_t *_new_simple_list_item(void *value)
{
	simple_list_item_t *new = calloc(1, sizeof(simple_list_item_t));
	if (new) {
		new->value = value;
	}
	return new;
}

void _destroy_simple_list_item(simple_list_item_t **item_ptr)
{
	if (item_ptr && *item_ptr) {
		free((*item_ptr));
		*item_ptr = NULL;
	}
}

simple_list_t *_new_simple_list(void)
{
	simple_list_t *list = NULL;
	list = calloc(1, sizeof(simple_list_t));
	return list;
}

int _insert_item_to_simple_list_before(simple_list_t *list, 
					simple_list_item_t *item, 
					simple_list_item_t *before)
{
	if (list && item) {
		before = before ? before : list->head;
		if (before) {
			item->prev = before->prev;
			item->next = before;
			if (before->prev)
				before->prev->next = item;
			else
				list->head = item;
		} else {
			item->prev = NULL;
			item->next = NULL;
			list->head = item;
			list->tail = item;
		}
		return 1;
	}
	return 0;
}

int _insert_item_to_simple_list_after(simple_list_t *list, 
				simple_list_item_t *item, 
				simple_list_item_t *after)
{
	if (list && item) {
		after = after ? after : list->tail;
		if (after) {
			item->prev = after;
			item->next = after->next;
			if (after->next)
				after->next->prev = item;
			else
				list->tail = item;
		} else {
			item->prev = NULL;
			item->next = NULL;
			list->head = item;
			list->tail = item;
		}
		return 1;
	}
	return 0;
}

int _del_item_from_simple_list(simple_list_t *list, 
				simple_list_item_t *item)
{
	if (list && item) {
		if (item->prev)
			item->prev->next = item->next;
		else 
			list->head = item->next;

		if (item->next)
			item->next->prev = item->prev;
		else
			list->tail = item->prev;

		return 1;
	}
	return 0;
}

simple_list_item_t *
_search_item_in_simple_list(simple_list_t *list,
			simple_list_item_t *start, 
			void *value)
{
	if (list && value) {
		unsigned int len = strlen(value);
		start = start ? start : list->head;
		while (start) {
			if ((strlen(start->value) == len) && !strcmp(value, start->value))
				break;
			start = start->next;
		}
		return start;
	}
	return NULL;
}

simple_list_item_t *
_search_item_in_simple_list_reverse(simple_list_t *list,
				simple_list_item_t *start,
				void *value)
{
	if (list && value) {
		unsigned int len = strlen(value);
		start = start ? start : list->tail;
		while (start) {
			if ((strlen(start->value) == len) && !strcmp(value, start->value))
				break;
			start = start->prev;
		}
		return start;
	}
	return NULL;
}

simple_list_item_t *
_get_simple_list_head(simple_list_t *list)
{
	if (list) 
		return list->head;
}

simple_list_item_t *
_get_simple_list_tail(simple_list_t *list)
{
	if (list)
		return list->tail;
}

simple_list_item_t *
_next_simple_list_item(simple_list_item_t *item)
{
	return item ? item->next : NULL;
}

simple_list_item_t *
_prev_simple_list_item(simple_list_item_t *item)
{
	return item ? item->prev : NULL;
}

void _destroy_simple_list(simple_list_t **list_ptr)
{
	if (list_ptr && *list_ptr) {
		simple_list_item_t *item = NULL;
		while (item = _get_simple_list_head(*list_ptr))
			_del_item_from_simple_list(*list_ptr, item);
	}
}

