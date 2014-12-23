#ifndef __array_H__
#define __array_H__

typedef int (*array_cmp_func)(void *first, void *second);

typedef int (*array_del_func)(void *data);

typedef struct __array_t {
	unsigned int count;
	void	**items;
} array_t;

array_t *new_array(void);
void destroy_array(array_t **parray, array_del_func del);
int add_array_item(array_t *array, void *item);
void remove_array_item(array_t *array, array_del_func del);
void *get_array_item(array_t *array, int index);
int  count_array(array_t *array);
void *replace_array_item(array_t *array, int index, void *with);
void *clear_array_item(array_t *array, int index);
void cleanup_array(array_t *array);
int compare_arrays(array_t *one, array_t *two, array_cmp_func cmp);
int find_in_array(array_t *array, void *key, int start_ix, array_cmp_func cmp);
int split_array(array_t *orig, int ix, array_t **first, array_t **second);
int merge_arrays(array_t **to, array_t **with);

#endif
