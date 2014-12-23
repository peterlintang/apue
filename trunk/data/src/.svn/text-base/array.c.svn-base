
#include <stdlib.h>	/* for calloc & free */
#include <string.h>	/* for memcpy & memmove */
#include "array.h"

array_t *new_array(void)
{
	array_t *array = calloc(1, sizeof(*array));
/*
	if (array) {
	}
*/
	return array;
}

void destroy_array(array_t **parray, array_del_func del)
{
	array_t *array = NULL;

	if (!parray || !(*parray)) return ;

	array = *parray;

	if (del) {
		while (count_array(array)) {
			remove_array_item(array, del);
		}
	}

	if (array->items) free(array->items);
	free(array);
	*parray = NULL;
}

int add_array_item(array_t *array, void *item)
{
	if (!array || !item) return -1;

	array->items = realloc(array->items, 
					(array->count + 1) * sizeof (void *));
	if (!array->items) return -1;		/* big error */

	memset(&array->items[array->count], 0, sizeof(void *));
	array->items[array->count] = item;
	array->count++;

	return array->count;
}

void remove_array_item(array_t *array, array_del_func del)
{
	if (!array || !array->count 
		|| !array->items[array->count - 1]) return ;

	if (del) (*del)(array->items[array->count - 1]);
	else free(array->items[array->count - 1]);
	array->items[--array->count] = NULL;
}

void *get_array_item(array_t *array, int index)
{
	if (!array || index < 0 || index >= array->count) return NULL;
	return array->items[index];
}

int count_array(array_t *array)
{
	if (array) return array->count;
	return -1;
}

void *replace_array_item(array_t *array, int index, void *with)
{
	void *prev = NULL;

	if (!array || index < 0 || index >= array->count) return NULL;
	
	prev = array->items[index];
	array->items[index] = with;
	return prev;
}

void *clear_array_item(array_t *array, int index)
{
	void *prev = NULL;

	if (!array || index < 0 || index >= array->count) return NULL;

	prev = array->items[index];
	array->items[index] = NULL;

	return prev;
}

void cleanup_array(array_t *array)
{
	int	     ix = 0;
	int	     jx = 0;
	unsigned int real_count = 0;
	void	     **new_items = NULL;

	if (!array) return ;

	while (ix < array->count) {
		if (array->items[ix]) real_count++;
		ix++;
	}
	if (real_count == array->count) return ;

	new_items = calloc(real_count, sizeof(void *));
	if (!new_items) return ;	/* big problem */

	ix = 0;
	while (ix < array->count) {
		if (array->items[ix]) {
			new_items[jx] = array->items[ix];
			jx++;
		}
		ix++;
	}

	free(array->items);
	array->items = new_items;
	array->count = real_count;
}

int compare_arrays(array_t *one, array_t *two, array_cmp_func cmp)
{
	int	ix = 0;
	int	match = 0;

	if (!one || !two || !cmp) return -1;	/* error */

	for (ix = 0; ix < one->count; ix++) {
		if (!one->items[ix] || !two->items[ix]) break;
		if (!(*cmp)(one->items[ix], two->items[ix])) break;
		match++;
	}
	return match;
}

int find_in_array(array_t *array, void *key, int start_ix, array_cmp_func cmp)
{
	int	ix = 0;

	if (!array || !key || !cmp || start_ix < 0) return -1;

	for (ix = start_ix; ix < array->count; ix++) {
		if (!array->items[ix]) continue;
		if (!(*cmp)(array->items[ix], key)) break;
	}
	return ix;
}

int split_array(array_t *orig, int ix, array_t **first, array_t **second)
{
	if (!orig || ix >= orig->count || ix < 0 
		|| !first || !second) return -1;	/* error */

	(*second) = new_array();
	if (!(*second)) return 0;

	(*second)->count = orig->count - ix;
	(*second)->items = malloc(sizeof(void *) * (*second)->count);
	if (!(*second)->items) {
		destroy_array(second, NULL);
		return 0;
	} else {
		memcpy(&(*second)->items, &orig->items[ix], 
			sizeof(void *) * (*second)->count);
	}

	(*first) = orig;
	(*first)->count = ix;
	(*first)->items = realloc(orig->items, sizeof(void *) * ix);
	if (!(*first)->items) {
		destroy_array(second, NULL);
		return 0;
	}

	return 1;
}

int merge_arrays(array_t **to, array_t **with)
{
	if (!to || !(*to)|| !with || !(*with)) return -1;

	(*to)->items = realloc((*to)->items, 
			sizeof(void *) * ((*to)->count + (*with)->count));
	if (!(*to)->items) return 0;

	memmove(&(*to)->items[(*to)->count], (*with)->items, 
		sizeof(void *) * (*with)->count);
	(*to)->count += (*with)->count;
	destroy_array(with, NULL);

	return (*to)->count;
}
