
/*
 * just test inifile parse  can work or 
 * not,  
 */

#include <stdio.h>
#include <stdlib.h>
#include "inifile.h"

int main(int argc, char *argv[])
{
	char		*value = NULL;
	category_t	*category = NULL;
	configuration_t *config = _parse_inifile(argv[1]);

	if (config)
	        fprintf(stdout, "parse file Ok\n");
	else {
		fprintf(stderr, "parse file error\n");
		exit(1);
	}

	category = _search_category_by_name(config, "linux");
	if (category) fprintf(stdout, "found %s\n", category->name);
	else fprintf(stdout, "not found %s\n", "linux");

	value = _get_param_value_category(category, "name");
	if (value) fprintf(stdout, "found name: %s\n", value);
	else fprintf(stdout, "not found \n");

	category = _search_category_by_name(config, "win");
	if (category) fprintf(stdout, "found %s\n", category->name);
	else fprintf(stdout, "not found %s\n", "win");

	value = _get_param_value_category(category, "name");
	if (value) fprintf(stdout, "found name: %s\n", value);
	else fprintf(stdout, "not found \n");
        fprintf(stdout, "------------show parameters-------------\n");
        fprintf(stdout, "OK\n");

	_destroy_configuration(&config);

        return 0;
}

