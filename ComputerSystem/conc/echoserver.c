#include <csapp.h>

void echo(int connfd);

void sigchld_handler(int flag)
{
	while(waitpid(-1, 0, WNOHANG) > 0)
		;
	return;
}

int main(int argc, char **argv)
{
	int listenfd, connfd, port;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;

	if(2 != argc) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(0);
	}
	
	port = atoi(argv[1]);

	Signal(SIGCHLD, sigchld_handler);

	listenfd = Open_listenfd(port);
	while(1) {
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

		if(Fork() == 0) {
			Close(listenfd);
			hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
								sizeof(clientaddr.sin_addr.s_addr), AF_INET);
			haddrp = inet_ntoa(clientaddr.sin_addr);
			printf("server connected to %s (%s)\n", hp->h_name, haddrp);
			echo(connfd);
			Close(connfd);
			exit(0);
		}
		Close(connfd);
	}
	exit(0);
}
