/*
 * implement the common_addr & server_addr & client_addr 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common_addr.h"


common_addr_t *new_common_addr(const int af, const uint16_t port, 
				const char *ipstr)
{
	common_addr_t *common_addr = calloc(1, sizeof(common_addr_t));

	if (common_addr) {
		common_addr->ipstr = strdup(ipstr);
		if (common_addr->ipstr)	{
			common_addr->af   = af;
			common_addr->port = port;
		} else {
			free(common_addr);
			return NULL;
		}
	}

	return common_addr;
}

void destroy_common_addr(common_addr_t **ppcommonaddr)
{
	if (ppcommonaddr && *ppcommonaddr) {
		free((*ppcommonaddr)->ipstr);
		free(*ppcommonaddr);
		*ppcommonaddr = NULL;
	}
}


int set_common_addr(common_addr_t *pcommonaddr, const int af,
		const uint16_t port, const char *ipstr,
		unsigned int flags)
{
	char *tmp;
	int   ret = 0;


	if (!pcommonaddr)
		return -2;

	if (flags & AF_MASK)
		pcommonaddr->af = af;
	if (flags & PORT_MASK)
		pcommonaddr->port = port;

	tmp = pcommonaddr->ipstr;
	if ((flags & IPSTR_MASK) && (pcommonaddr->ipstr = strdup(ipstr))) {
		free(tmp);
	} else {
		pcommonaddr->ipstr = tmp;
		ret = -1;
	}

	return ret;
}

void clear_common_addr(common_addr_t *pcommonaddr, unsigned int flags)
{
	if (!pcommonaddr)
		return ;

	if (flags & AF_MASK)
		pcommonaddr->af = -1;

	if (flags & PORT_MASK)
		pcommonaddr->port = 0;

	if (flags & IPSTR_MASK) {
		free(pcommonaddr->ipstr);
		pcommonaddr->ipstr = NULL;
	}
}

