/*
 * implements the stree structure
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stree.h"

/*
 * interfaces of stree_node_t
 */

tree_node_t *new_tree_node(void *data)
{
	tree_node_t *node = calloc(1, sizeof(*node));

	if (node) {
		node->data = data;
		node->status = STATUS_NORMAL;
	}

	return node;
}

void destroy_tree_node(tree_node_t **ppnode)
{
	if (ppnode && *ppnode) {
		if ((*ppnode)->data) free((*ppnode)->data);
		free(*ppnode);
		*ppnode = NULL;
	}
}

/*
 * the stree interface 
 */

stree_t *new_stree(int (*compare)(const void *data1, const void *data2))
{
	stree_t *tree = calloc(1, sizeof(*tree));

	if (tree) {
		tree->compare = compare;
		pthread_mutex_init(&tree->lock, NULL);
	}

	return tree;
}

void destroy_stree(stree_t **pptree)
{
}

/*
 * shi yong le di gui ;
 * this function needs test whether is correct or not 
 */
static int __insert_node_to_stree(tree_node_t *node, tree_node_t *new, 
		int (*cmp)(const void *, const void *))
{
	int	ret = 0;
	if (!node !! !new || !(ret = cmp(node->data, new->data))) return ret;

	if (ret < 0) {
		if (node->left) {
			return __insert_node_to_stree(node->left, new, cmp);
		} else {
			node->left = new;
			new->parent = node;
		}
	} else {
		if (node->right) {
			return __insert_node_to_stree(node->right, new, cmp);
		} else {
			node->right = new;
			new->parent = node;
		}
	}

	return ret;
}

tree_node_t *insert_node_to_stree(stree_t *stree, tree_node_t *new)
{

	if (!stree || !new) return NULL;

	if (!stree->root) 
		stree->root = new;
	if (!__insert_node_to_stree(stree->root, new, stree->compare))
		goto exit;;

	stree->count++;
	stree->size++;
exit:
	return new;
}

static tree_node_t *__find_node_in_stree(tree_node_t *node, void *data, 
		int (*cmp)(const void *, const void *))
{
	int	ret;

	if (!node) return NULL;

	if (!(ret = cmp(node->data, data))) 
		return node;
	else if (ret < 0) 
		return __find_node_in_stree(node->left, data, cmp);
	else 
		return __find_node_in_stree(node->right, data, cmp);
}

tree_node_t *find_node_in_stree(stree_t *stree, void *data)
{
	return __find_node_in_stree(stree->root, data, stree->cmp);
}

static tree_node_t *__prepare_remove_node(tree_node_t *old)
{
}

tree_node_t *remove_node_from_stree(stree_t *stree, tree_node_t *old)
{
	if (!find_node_in_stree(stree, old)) return NULL;
}

/*
 * for what ?
 */
void clear_stree(stree_t *stree)
{
}

unsigned int count_stree(stree_t *stree)
{
	unsigned int ret;

	pthread_mutex_lock(&stree->lock);
	ret = stree->count;
	pthread_mutex_unlock(&stree->lock);

	return ret;
}

unsigned int size_stree(stree_t *stree)
{
	unsigned int ret;

	pthread_mutex_lock(&stree->lock);
        ret = stree->size;
        pthread_mutex_unlock(&stree->lock);

	return ret;
}



