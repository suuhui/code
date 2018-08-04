#include <csapp.h>

int main(int argc, char **argv)
{
	struct in_addr inaddr;
	unsigned int hex;
	if(2 != argc) {
		fprintf(stderr, "Usage %s <dotted-decimal>\n", argv[0]);
		exit(0);
	}

	if(inet_aton(argv[1], &inaddr) == 0) {
		fprintf(stderr, "inet_aton error");
		exit(0);
	}
	hex = ntohl(inaddr.s_addr);
	printf("0x%x\n", hex);
}
