
/*
 * just test parse_params can work or 
 * not,  
 */
#include <stdio.h>
#include <stdlib.h>
#include "parse_params.h"

int main(int argc, char *argv[])
{
        parameters_t *params = parse_parameters(argc, argv);
        fprintf(stdout, "parse Ok\n");

        fprintf(stdout, "------------show parameters-------------\n");
        param_t *param = params->first;
        while (param) {
                fprintf(stdout, "key: %s value: %s\n", param->key, param->value);
                param = param->next;
        }


        fprintf(stdout, "destroy params... ");
	clean_parse_parameters(params);
//        _destroy_parameters(&params);
        fprintf(stdout, "OK\n");

        return 0;
}

