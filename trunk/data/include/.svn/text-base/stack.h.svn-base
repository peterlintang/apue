#ifndef __stack_H__
#define __stack_H__

typedef struct __stack_item_t {
	void	*data;
	struct __stack_item_t *next;
} stack_item_t;

stack_item_t *new_stack_item(void *data);
void destroy_stack_item(stack_item_t **pold, int force);

typedef struct __stack_t {

	char	*name;
	unsigned int id;

	struct __stack_t *next;

	struct __stack_item_t *head;
	unsigned int count;
} stack_t ;

stack_t *new_stack(char *name, unsigned int id);
void destroy_stack(stack_t **pstack);
void *in_stack(stack_t *stack, void *data);
void *out_stack(stack_t *stack);
int is_empty_stack(stack_t *stack);

#endif
