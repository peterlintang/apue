/*
 8 the common address which will be used by client & server
 */

#ifndef _COMMON_ADDR_H
#define _COMMON_ADDR_H

#include <netinet/in.h>	/* uint16_t needed */

#define SET_AF		(1 << 0)
#define SET_PORT 	(1 << 1)
#define SET_IPSTR	(1 << 2)

#define AF_MASK		0x00000001
#define PORT_MASK	0x00000002
#define IPSTR_MASK	0x00000004

typedef struct {
	char		*ipstr;
	uint16_t	 port;
	int		 af;
} common_addr_t;

typedef common_addr_t server_addr_t;
typedef common_addr_t client_addr_t;

common_addr_t *new_common_addr(const int af, const uint16_t port, const char *ipstr);

void destroy_common_addr(common_addr_t **ppcommonaddr);

int set_common_addr(common_addr_t *commonaddr, const int af, 
		const uint16_t port, const char *ipstr, unsigned int flags);

void clear_common_addr(common_addr_t *pcommonaddr, unsigned int flags);

static inline client_addr_t *new_client_addr(const int af, 
		const uint16_t port, const char *ipstr)
{
	return (client_addr_t *) new_common_addr(af, port, ipstr);
}

static inline void destroy_client_addr(client_addr_t **ppclient_addr)
{
	destroy_common_addr((common_addr_t **)ppclient_addr);
}

static inline server_addr_t *new_server_addr(const int af, 
		const uint16_t port, const char *ipstr)
{
	return (server_addr_t *) new_common_addr(af, port, ipstr);
}

static inline void destroy_server_addr(server_addr_t **ppserver_addr)
{
	destroy_common_addr((common_addr_t **)ppserver_addr);
}

static inline int set_server_addr(server_addr_t *server, const int af, 
		const uint16_t port, const char *ipstr, unsigned int flags)
{
	return set_common_addr((common_addr_t *)server, af, port, ipstr, flags);
}

static inline void clear_server_addr(server_addr_t *server, unsigned int flags)
{
	clear_common_addr((common_addr_t *)server, flags);
}

static inline int set_client_addr(client_addr_t *client, const int af, 
		const uint16_t port, const char *ipstr, unsigned int flags)
{
	return set_common_addr((common_addr_t *)client, af, port, ipstr, flags);
}

static inline void clear_client_addr(client_addr_t *client, unsigned int flags)
{
	clear_common_addr((common_addr_t *)client, flags);
}

#endif // _COMMON_ADDR_H
