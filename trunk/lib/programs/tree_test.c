/*
 * have a test of tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_tree.h"

uint32_t cmp(const void *data1, const void *data2)
{
	return 0;
}

int main(int argc, char *argv[])
{
	simple_tree_node_t *tmp = NULL;
	simple_tree_node_t *node = NULL;
	node = calloc(1, sizeof(*node));
	node->data = malloc(40 * sizeof(char));
	simple_tree_t *tree = _new_simple_tree(strcmp);

	if (!tree || !node || !node->data) {
		fprintf(stderr, "no memory\n");
		free(tree);
		free(node);
		return 0;
	}

	strcpy(node->data, "hello world");

	if (_insert_node_to_simple_tree(tree, node))
		fprintf(stdout, "insert OK\n");

	/* second element */
	node = calloc(1, sizeof(*node));
	node->data = malloc(40 * sizeof(char));
	strcpy(node->data, "hello john");

	if (_insert_node_to_simple_tree(tree, node))
		fprintf(stdout, "insert OK\n");

/*
	if (tmp = _search_node_simple_tree(tree, "hello world"))
		fprintf(stdout, "node : %p, data: %s\n", tmp, (char *)tmp->data);
*/

	if (tmp = _search_node_simple_tree(tree, "hello john"))
		fprintf(stdout, "node : %p, data: %s\n", tmp, (char *)tmp->data);

	_destroy_simple_tree(&tree);
	fprintf(stdout, "tree: %p\n", tree);
	fprintf(stdout, "node : %p, data: %s\n", tmp, (char *)tmp->data);
	return 0;
}
