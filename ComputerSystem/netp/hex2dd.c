#include <csapp.h>

int main(int argc, char **argv)
{
	struct in_addr inaddr;
	unsigned int addr;
	if(2 != argc) {
		fprintf(stderr, "Usage %s <hex number>\n", argv[0]);
		exit(0);
	}

	sscanf(argv[1], "%x", &addr);
	inaddr.s_addr = htonl(addr);
	printf("%d\n", htonl(addr));
	printf("%s\n", inet_ntoa(inaddr));
}
