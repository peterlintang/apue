/* 
 * test for cquark interfaces 
 */

#include <stdio.h>
#include <stdlib.h>

#include "cquark.h"

int fun1 = 0;
int fun2 = 0;

int quark_func_1(void *data)
{
	while (++fun1 < 4) {
		fprintf(stdout, "%s : hello world, we are %s\n", __func__, __func__);
		return 1;
	}
	return 0;
}

int quark_func_2(void *data)
{
	while (++fun2 < 4) {
		fprintf(stdout, "%s : hello world, we are %s\n", __func__, __func__);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	quark_t *quark = NULL;
	cquark_item_t *cquark_item = NULL;
	cquark_item_t *cquark_item2 = NULL;
	cquark_t *cquark = NULL;

	fprintf(stdout, "creating my cquark\n");
	cquark = _new_cquark("my cquark 1");
	if (!cquark) {
		perror("_new_cquark");
		exit(1);
	} else {
		cquark_item_t *tmp = _get_head_cquark(cquark);
		fprintf(stdout, "%s : tmp %p\n", __func__, tmp);
	}

	/* first */
	fprintf(stdout, "creating quark 1\n");
	quark = _new_quark(quark_func_1, NULL);
	if (!quark) {
		perror("_new_quark");
		_destroy_cquark(&cquark);
		exit(2);
	}

	fprintf(stdout, "creating cquark item 1\n");
	cquark_item = _new_cquark_item(quark);
	if (!cquark_item) {
		perror("_new_cquark_item");
		_destroy_quark(&quark);
		_destroy_cquark(&cquark);
		exit(3);
	}

	fprintf(stdout, "insert cquark item 1 to cquark\n");
	if (!_insert_item_before_cquark(cquark, cquark_item, NULL)) {
		perror("_insert_item_before_cquark");
		_destroy_cquark_item(&cquark_item);
		_destroy_cquark(&cquark);
		exit(4);
	}


	/* second */
	fprintf(stdout, "creating quark 2\n");
	quark = _new_quark(quark_func_2, NULL);
	if (!quark) {
		perror("_new_quark");
		_destroy_cquark(&cquark);
		exit(2);
	}

	fprintf(stdout, "creating cquark item 2\n");
	cquark_item = _new_cquark_item(quark);
	if (!cquark_item) {
		perror("_new_cquark_item");
		_destroy_quark(&quark);
		_destroy_cquark(&cquark);
		exit(3);
	}

	fprintf(stdout, "insert cquark item 2 to cquark\n");
	if (!_insert_item_before_cquark(cquark, cquark_item, NULL)) {
		perror("_insert_item_before_cquark");
		_destroy_cquark_item(&cquark_item);
		_destroy_cquark(&cquark);
		exit(4);
	}

	fprintf(stdout, "all OK\n");

	/* now let's do the action */

	cquark_item = _get_head_cquark(cquark);
	if (cquark_item) {
		_spin_quark(cquark_item->quark);
		if (!_insert_item_after_cquark(cquark, cquark_item, NULL)) {
			perror("_insert_item_after_cquark");
			_destroy_cquark_item(&cquark_item);
		}
//		sleep(1);
//		_destroy_cquark_item(&cquark_item);
	}

//	sleep(4);
	cquark_item2 = _get_head_cquark(cquark);
	if (cquark_item2) {
		_spin_quark(cquark_item2->quark);
		if (!_insert_item_after_cquark(cquark, cquark_item2, NULL)) {
			perror("_insert_item_after_cquark");
			_destroy_cquark_item(&cquark_item2);
		}
//		sleep(1);
//		_destroy_cquark_item(&cquark_item2);
	}

	sleep(2);

	//_destroy_cquark_item(&cquark_item);
	//_destroy_cquark_item(&cquark_item2);

	fprintf(stdout, "where 4\n");
	_destroy_cquark(&cquark);
	fprintf(stdout, "destroy OK\n");
	return 0;
}


