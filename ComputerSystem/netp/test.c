#include <csapp.h>
#define M 1024
int main()
{
	int fd;
	char *buf;
	rio_t rio;
	fd = open("hex2dd.c", O_RDONLY, 0);
	printf("fd is %d\n", fd);
	Rio_readinitb(&rio, fd);
	//rio_readnb(&rio, buf, 10240);
	rio_readlineb(&rio, buf, M);
	printf("%s\n", buf);
}
