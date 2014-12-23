/*
 * hash table
 */

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

typedef struct __hash_t {

	unsigned int	M;
	list_head 	**table;		/* array of lists ( space M * sizeof(list_head) ) */
	unsigned int	(*hash)(const void *, unsigned int M);

} hash_t;

hash_t *create_hash(unsigned int M, unsigned int (*hash)(const void *, unsigned int M));
void destroy_hash(hast_t **);

#endif	// end of _HASH_TABLE_H
