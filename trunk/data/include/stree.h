/*
 * implements the simple tree
 */

#ifndef SIMPLE_TREE_H
#define SIMPLE_TREE_H


typedef struct __tree_node_t {
	void	*data;

	struct __tree_node_t *parent;
	struct __tree_node_t *left;
	struct __tree_node_t *right;

	unsigned char status;
#define STATUS_UNDEF	0x00000000
#define STATUS_DELETED	0x00000001
#define STATUS_NORMAL	0x00000002

} tree_node_t;

tree_node_t *new_tree_node(void *data);
void destroy_tree_node(tree_node_t **ppnode);


typedef struct __stree_t {
	tree_node_t *root;
	int (*compare)(const void *, const void *);

	unsigned int count;	// why need two these two 
	unsigned int size;	//

	pthread_mutex_t lock;	// should have thread support	// will use in the future , hei hei 
} stree_t;

stree_t *new_stree(int (*compare)(const void *, const void *));
void destroy_stree(stree_t **ppstree);
static int __insert_node_to_stree(tree_node_t *node, tree_node_t *new,  
                int (*cmp)(const void *, const void *));
tree_node_t *insert_node_to_stree(stree_t *stree, tree_node_t *new);
static tree_node_t *__find_node_in_stree(tree_node_t *node, void *data,
                int (*cmp)(const void *, const void *));
tree_node_t *find_node_in_stree(stree_t *stree, void *data);
tree_node_t *remove_node_from_stree(stree_t *stree, tree_node_t *old);
void clear_stree(stree_t *stree);
unsigned int count_stree(stree_t *stree);
unsigned int size_stree(stree_t *stree);



#endif // SIMPLE_TREE_H
