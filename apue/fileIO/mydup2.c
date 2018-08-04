#include "../apueerr.h"
#include <fcntl.h>

#define MAX 4096

int mydup2(int filedes, int fileds2);

int main(int argc, char **argv)
{
	int fd;
	if(argc != 3) {
		err_sys("Usage: ./mydup2 <file> <newfd>\n");
		return -1;
	}

	char *name = argv[1];
	fd = open((const char *)name, O_RDWR);
	if(fd < 0) {
		err_sys("open file error\n");
		return -1;
	}
	fd = mydup2(fd, atoi(argv[2]));
	printf("new fd is %d\n", fd);
	return fd;
}

int mydup2(int f1, int f2)
{
	int stack[MAX];
	int top = 0;
	int fd;
	int i;

	if(f1 > MAX || f2 < 0) {
		err_sys("invalid fd");
		return -1;
	}

	while((fd = dup(1)) < f2) {
		if(fd == -1) {
			err_sys("dup error");
			return -1;
		}

		stack[top++] = fd;
	}

	for(i=0; i<top; i++) {
		close(stack[i]);	
	}
	return f2;
}
