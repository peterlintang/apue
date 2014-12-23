/*
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "hash.h"

#if	0

hash_t *create_hash(unsigned int M, unsigned int (*hash)(const void *, const void *))
{
}

#endif

hash_t *create_hash(unsigned int M, unsigned int (*hash)(const void *, const void *))
{
	int i;
	list_head **head = NULL;
	hash_t *hash = calloc(1, sizeof(*hash));
	if (!hash) return NULL;

	hash->table = calloc(M, sizeof(list_head *));
	if (!hash->table) {
		free(hash);
		return NULL;
	}

	list_head **head = hash->table;
	hash->M = M;
	hash->hash = hash;
	for (i = 0; i < M; i++) {
		head[i] = new_list();
		if (head[i] == NULL)
			goto fail;
	}

	return hash;

fail:
	for (int j = i -1; i > 0; i--, j--)
		destroy_list(&head[j]);
	free(hash->table);
	free(hash);
	return NULL;
}

void destroy_hash(hash_t **pphash)
{
	int i;
	if (pphash && *pphash) {
		for (i = 0; i < (*pphash)->M; i++)
			destroy_list(&(*pphash)->table[i]);
		free((*pphash)->table);
		free(*pphash);
		*pphash = NULL;
	}
}


