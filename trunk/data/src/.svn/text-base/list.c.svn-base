/*
 * implements the interface of list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/*
 * interface of list node 
 */
list_node_t *new_list_node(void *data)
{
	list_node_t *node = calloc(1, sizeof(*node));
	if (node)
		node->data = data;

	return node;
}

void destroy_list_node(list_node_t **ppnode)
{
	if (ppnode && *ppnode) {
		free((*ppnode)->data);
		free(*ppnode);
		*ppnode = NULL;
	}

}


/*
 * interface of list 
 */
list_head *new_list(void)
{
	list_head *head = calloc(1, sizeof(*head));
	if (head) {
		pthread_mutex_init(&head->lock, NULL);
	}

	return head;
}

void destroy_list(list_head **pplist)
{
	list_node_t *tmp = NULL;

	if (pplist && *pplist) {
		while ((tmp = drop(*pplist)) != NULL)
			destroy_list_node(&tmp);
		pthread_mutex_destroy(&(*pplist)->lock);
		free(*pplist);
		*pplist = NULL;
	}
}


list_node_t *insert_node_after(list_head *list, list_node_t *new, list_node_t *after)
{
	if (!list || !new) return NULL;

	pthread_mutex_lock(&list->lock);

	if (!list->head) {
		list->head = new;
		new->prev = new;
		new->next = new;
	} else if (!after) {
		new->next = list->head;
		new->prev = list->head->prev;
		list->head->prev->next = new;
		list->head->prev = new;
		list->head = new;
	} else {
		new->next = after->next;
		new->prev = after;
		after->next->prev = new;
		after->next = new;
	}
	list->count += 1;

	pthread_mutex_unlock(&list->lock);

	return new;
}

list_node_t *insert_node_before(list_head *list, list_node_t *new, list_node_t *before)
{
	if (!list || !new) return NULL;

	pthread_mutex_lock(&list->lock);

	if (!list->head) {
		list->head = new;
		new->prev = new;
		new->next = new;
	} else if (!before) {
		new->next = list->head;
		new->prev = list->head->prev;
		list->head->prev->next = new;
		list->head->prev = new;
		list->head = new;
	} else {
		new->next = before;
		new->prev = before->prev;
		before->prev->next = new;
		before->prev = new;
	}
	list->count++;

	pthread_mutex_unlock(&list->lock);

	return new;
}

list_head *list_reverse(list_head *list)
{
	list_head *new_list = new_list();

	if (list && new_list) {
		list_node_t *tmp;
		while ((tmp = pop(list)) != NULL) {
			insert_node_before(new_list, tmp, new_list->head);
		}
		destroy_list(&list);
	} else {
		destroy_list(&new_list);
	}

	return new_list;
}

int list_count(list_head *list)
{
	pthread_mutex_lock(&list->lock);
	return list ? list->count : -1;
	pthread_mutex_unlock(&list->lock);
}

int list_is_empty(list_head *list)
{
/*
	if (!list) return -1;

	if (list->head) return 1;
	else return 0;
*/
	pthread_mutex_lock(&list->lock);
	return list ? (list->head ? 0 : 1) : -1;
	pthread_mutex_unlock(&list->lock);
}

/*
 * the caller should held the @list->lock
 */
static int node_in_list(list_head *list, list_node_t *node)
{
	list_node_t *tmp = NULL;

	if (!list || !list->head || !node) return 0;

	for (int i = 0, tmp = list->head; i < list->count; i++, tmp = tmp->next) {
		if (tmp == node) return 1;
	}

	return 0;
}

list_node_t *remove_node(list_head *list, list_node_t *old)
{
	pthread_mutex_lock(&list->lock);
	if (!list || !list->count 
		|| !old || !node_in_list(list, node)) 
		return NULL;

	if (list->count == 1) {
		list->head = NULL;
	} else if (old == list->head) {
		list->head = old->prev;
	}

	old->next->prev = old->prev;
	old->prev->next = old->next;
	old->next = NULL;
	old->prev = NULL;

	list->count--;
	pthread_mutex_unlock(&list->lock);

	return old;
}

list_node_t *pop(list_head *list)
{
	return list ? remove_node(list, list->head) : NULL;
}

list_node_t *drop(list_head *list)
{
	return list ? remove_node(list, list->head->prev) : NULL;
}

list_node_t *first(list_head *list)
{
	pthread_mutex_lock(&list->lock);
	return list ? list->head : NULL;
	pthread_mutex_unlock(&list->lock);
}

list_node_t *last(list_head *list)
{
	pthread_mutex_lock(&list->lock);
	return list && list->head ? list->head->prev : NULL;
	pthread_mutex_unlock(&list->lock);
}

list_node_t *next(list_node_t *node)
{
	return node ? node->next : NULL;
}

list_node_t *prev(list_node_t *node)
{
	return node ? node->prev : NULL;
}

