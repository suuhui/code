#include <csapp.h>
#define M 128 
int main()
{
	int fd;
	char *buf;
	int i = 0;
	rio_t rio;
	fd = open("hex2dd.c", O_RDONLY, 0);
	printf("fd is %d\n", fd);
	Rio_readinitb(&rio, fd);
	//rio_readnb(&rio, buf, 10240);
	i = rio_readlineb(&rio, buf, M);
	while(strcmp(buf, "{\n")) {
		printf("%s", buf);	
		i = Rio_readlineb(&rio, buf, M);
	}
	while(i != 0) {
		printf("%s", buf);
		i = Rio_readlineb(&rio, buf, M);
	}
	Rio_readlineb(&rio, buf, M);

	printf("last: %s", buf);
}
