#include <csapp.h>

int main(int argc, char **argv)
{
	struct in_addr addr;
	struct hostent *hostp;
	char **pp;

	if(2 != argc) {
		fprintf(stderr, "Usage: %s <domain name or dotted-decimal>\n", argv[1]);
		exit(0);
	}
	if(inet_aton(argv[1], &addr) == 0)
		hostp = gethostbyname(argv[1]);
	else
		hostp = gethostbyaddr((const char *)&addr, sizeof(addr), AF_INET);
	
	printf("official hostname is: %s\n", hostp->h_name);

	for(pp = hostp->h_aliases; *pp != NULL; pp++)
		printf("alias: %s\n", *pp);

	for(pp = hostp->h_addr_list; *pp != NULL; pp++) {
		addr.s_addr = ((struct in_addr *)*pp)->s_addr;
		printf("address: %s\n", inet_ntoa(addr));
	}
	exit(0);
}

