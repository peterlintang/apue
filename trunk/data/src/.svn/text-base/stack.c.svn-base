
#include <stdlib.h>		/* for calloc & free */
#include <string.h>		/* for strdup  */
#include "stack.h"

stack_item_t *new_stack_item(void *data)
{
	stack_item_t *node = NULL;

	if (data) {
		node = (stack_item_t *)calloc(1, sizeof(*node));
		if (node) node->data = data;
	}
	return node;
}

void destroy_stack_item(stack_item_t **pold, int force)
{
	if (pold && *pold) {
		if (force && (*pold)->data) free((*pold)->data);
		free(*pold);
		*pold = NULL;
	}
}

stack_t *new_stack(char *name, unsigned int id)
{
	stack_t *stack = NULL;

	name = name ? name : "stack";

	stack = (stack_t *)calloc(1, sizeof(*stack));
	if (!stack) return NULL;

	stack->name = strdup(name);
	stack->id   = id;

	return stack;
}

void destroy_stack(stack_t **pstack)
{
}

void *in_stack(stack_t *stack, void *data)
{
	stack_item_t *node = NULL;

	if (!stack || !data) return NULL;

	node = new_stack_item(data);
	if (!node) return NULL;

	node->next = stack->head;
	stack->head = node;
	stack->count++;

	return data;
}

void *out_stack(stack_t *stack)
{
	void	     *data = NULL;
	stack_item_t *node = NULL;

	if (!stack || !stack->head) return NULL;

	node = stack->head;
	stack->head = node->next;
	stack->count--;

	data = node->data;
	destroy_stack_item(&node, 0);

	return data;
}

int is_empty_stack(stack_t *stack)
{
	if (stack) return stack->count ? 1 : 0;
	return -1;
}
