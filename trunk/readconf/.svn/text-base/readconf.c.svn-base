#include <fcntl.h>
#include "apue.h"

#define DEBUG
//#undef DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define BUFLENGTH               1024

#define PATH "./show.conf"

char *readpara(char *buf, char *para);
int strsearch(char *s1, char *s2);
int my_index(char *s1, int c);

int
main(int argc, char *argv[])
{
	int fd;
	int start;
	int length;
	int id;
	char *buf;
	char tmp[48];
	struct my_conf {
		char *at;
		char *inet;
		char *add;
		char *netmask;
	} my_conf;

	
	buf = malloc(BUFLENGTH);
	if (!buf)
	{
		errprintf("malloc error\n");
		exit(1);
	}
	else
		memset(buf, 0, BUFLENGTH);
	
	lseek(fd, 0, SEEK_SET);

	if (((fd = open(PATH, O_RDONLY)) < 0) || (read(fd, buf, BUFLENGTH) < 0))
	{
		errprintf("open or read conf file %s error\n", PATH);
		exit(1);
	}
	else
	{
		dprintf("read config:\n%s\n", buf);
	}

	my_conf.at 	= readpara(buf, "auto");
	my_conf.add	= readpara(buf, "address");
	my_conf.inet 	= readpara(buf, "inet");
	my_conf.netmask = readpara(buf, "netmask");



/*
	dprintf("\n\n\n---------read auto-----------\n\n\n");
	start = strsearch(buf, "auto");
	length   = my_index(&buf[start], '\n');
	if (length > 48)
	{
		errprintf("the str is too long\n");
		exit(1);
	}
	else
	{
		strncpy(tmp, &buf[start], length);
		tmp[length] = '\0';
		id = my_index(tmp, '=');
		my_conf.at = malloc(strlen(tmp) - id);
		strcpy(my_conf.at, &tmp[id + 1]);
		dprintf("auto: %s\n", my_conf.at);
	}
	
	dprintf("\n\n\n---------read inet-----------\n\n\n");
	start = strsearch(buf, "inet");
	length   = my_index(&buf[start], '\n');
	if (length > 48)
	{
		errprintf("the str is too long\n");
		exit(1);
	}
	else
	{
		strncpy(tmp, &buf[start], length);
		tmp[length] = '\0';
		id = my_index(tmp, '=');
		my_conf.inet = malloc(strlen(tmp) - id);
		strcpy(my_conf.inet, &tmp[id + 1]);
		dprintf("inet: %s\n", my_conf.inet);
	}

	dprintf("\n\n\n---------read address-----------\n\n\n");
	start = strsearch(buf, "address");
	length   = my_index(&buf[start], '\n');
	if (length > 48)
	{
		errprintf("the str is too long\n");
		exit(1);
	}
	else
	{
		strncpy(tmp, &buf[start], length);
		tmp[length] = '\0';
		id = my_index(tmp, '=');
		my_conf.add = malloc(strlen(tmp) - id);
		strcpy(my_conf.add, &tmp[id + 1]);
		dprintf("address: %s\n", my_conf.add);
	}

	dprintf("\n\n\n---------read netmask-----------\n\n\n");
	start = strsearch(buf, "netmask");
	length   = my_index(&buf[start], '\n');
	if (length > 48)
	{
		errprintf("the str is too long\n");
		exit(1);
	}
	else
	{
		strncpy(tmp, &buf[start], length);
		tmp[length] = '\0';
		id = my_index(tmp, '=');
		my_conf.netmask = malloc(strlen(tmp) - id);
		strcpy(my_conf.netmask, &tmp[id + 1]);
		dprintf("netmask: %s\n", my_conf.netmask);
	}
*/

/*
	id = my_index(buf,'\n');
	dprintf("my_index \\n: %d\n", id);
	snprintf(tmp, id + 1, "%s", buf);
	id = my_index(buf, '=');
	dprintf("my_index =: %d\n", id);
	dprintf("auto = %s\n", &tmp[id + 1]);
	//tmp[id] = '\0';
	dprintf("%s\n", tmp);

	if ((id = strsearch(tmp, "auto")) < 0)
		errprintf("not found\n");
	else
	{
		dprintf("found: %d\n", id);
		fprintf(stdout, "%s\n", &tmp[id]);
	}
*/
	if (my_conf.at)
		free(my_conf.at);
	if (my_conf.add)
		free(my_conf.add);
	if (my_conf.inet)
		free(my_conf.inet);
	if (my_conf.netmask)
		free(my_conf.netmask);

	free(buf);
	exit(0);


}


/*
 *search s2 in s1
 *return value:
 *index the start index in s1 
 *-1 no found
 */
int strsearch(char *s1, char *s2)
{
	int i, j;
	int len1, len2;

	i = 0;
	j = 0;
	len1 = strlen(s1);
	len2 = strlen(s2);

//	while (s1[i] != '\0' && s2[j] != '\0')
	while (1)
	{
		if (s1[i] == s2[j])
		{
			if (len2 == j + 1)
				return i - j;
			i++, j++;
		}
		else
		{
			j = 0;
			if (s1[i] != s2[j])
				i++;
		}
		if (s1[i] == '\0' || s2[j] == '\0')
			return -1;
	}
}

/*
 *find the first c appear in s1
 *return value:
 *the index in s1 success
 *-1 no found
 */
int my_index(char *s1, int c)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return i;
		else
			i++;
	}
	return -1;
}


/*
 *read *para from *buf
 *return the string contain the *para value
 */
char *readpara(char *buf, char *para)
{
	int start, length, id;
	char tmp[48];
	char *ptr;

	dprintf("\n\n\n---------read %s-----------\n\n\n", para);
	start = strsearch(buf, para); 
	length   = my_index(&buf[start], '\n');
	if (length > 48)
	{
		errprintf("the str is too long\n");
		return NULL;
	}
	else
	{
		strncpy(tmp, &buf[start], length);
		tmp[length] = '\0';
		id = my_index(tmp, '=');
		ptr = malloc(strlen(tmp) - id);
		strcpy(ptr, &tmp[id + 1]);
		dprintf("%s: %s\n", para, ptr);
	}
	return ptr;
}


