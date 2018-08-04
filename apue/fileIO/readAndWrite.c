#include "../apueerr.h"
#include <fcntl.h>
#define MAX 1024
int main()
{
	char buf[MAX];
	int fd1, fd2;
	const char *s1 = "hello world!\r\n";
	const char *s2 = "world hello!\r\n";
	fd1 = open("./a.txt", O_RDWR | O_APPEND);
	fd2 = open("./a.txt", O_RDWR | O_APPEND);

	write(fd1, (const void *)s1, strlen(s1));
	write(fd2, (const void *)s2, strlen(s2));
	return 0;
}
