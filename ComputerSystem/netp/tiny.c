#include <csapp.h>

void doit(int fd);
void read_requesthdrs(rio_t *rp);
void read_requestbody(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void get_filetype(char *filename, char *filetype);
void serve_static(int fd, char *filename, int filesize);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

int main(int argc, char **argv)
{
	int listenfd, connfd, port, clientlen;
	struct sockaddr_in clientaddr;

	if(2 != argc) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);	
		exit(0);
	}

	port = atoi(argv[1]);
	listenfd = Open_listenfd(port);

	while(1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		doit(connfd);
		Close(connfd);
	}
}

void doit(int fd)
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];
	rio_t rio;

	Rio_readinitb(&rio, fd);
	Rio_readlineb(&rio, buf, MAXLINE);
	sscanf(buf, "%s %s %s", method, uri, version);
	if(strcasecmp(method, "GET") == 0){
	
	} else if(strcasecmp(method, "POST") == 0){
		
	} else {
		clienterror(fd, method, "501", "Not Implemented",
					"Tiny does not implement this method");	
		return;
	}

	printf("####################request start########################\r\n");
	/* output first request header */
	printf("%s\n", buf);
	/* output other request header */
	read_requesthdrs(&rio);
	
	//read_requestbody(&rio);

	is_static = parse_uri(uri, filename, cgiargs);
	if(stat(filename, &sbuf) < 0) {
		clienterror(fd, filename, "404", "Not Found",
					"Tiny could't found this file");	
		return;
	}

	if(is_static) {
		/* Is this file regular file or Is user has permission to read */
		if(!S_ISREG(sbuf.st_mode) || !(S_IRUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
						"Tiny couldn't read the file");	
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
	} else {
		if(!S_ISREG(sbuf.st_mode) || !(S_IXUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
						"Tiny couldn't read the file");	
			return;
		}

		serve_dynamic(fd, filename, cgiargs);
	}
}

void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
				char *longmsg)
{
	char buf[MAXLINE], body[MAXLINE];

	sprintf(body, "<html><title>Tiny Error</title>");
	sprintf(body, "%s<body bgcolor=""#fff""\r\n", body);	
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>The Tiny Web Server</em>\r\n", body);

	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	Rio_writen(fd, buf, strlen(buf));
	Rio_writen(fd, body, strlen(body));
}

void read_requesthdrs(rio_t *rp)
{
	char buf[MAXLINE];
	int n; 
	n = Rio_readlineb(rp, buf, MAXLINE);
	while(strcmp(buf, "\r\n")) {
		printf("%s", buf);
		n = Rio_readlineb(rp, buf, MAXLINE);	
	}
	printf("#####################request end#######################\r\n");
	return;
}

void read_requestbody(rio_t *rp)
{
	char buf[MAXLINE];
	int n; //size of read 
	printf("######################request body##########################\r\n");
	n = Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
	while(n != 0) {
		n = Rio_readlineb(rp, buf, MAXLINE);	
		printf("%s", buf);
	}
	printf("####################request body end#####################\r\n");
	return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
	char *ptr;

	if(!strstr(uri, "cgi-bin")) {
		strcpy(cgiargs, "");	
		strcpy(filename, ".");
		strcat(filename, uri);
		if(uri[strlen(uri) - 1] == '/')
			strcat(filename, "home.html");
		return 1;
	} else {
		ptr = index(uri, '?');	
		if(ptr) {
			strcpy(cgiargs, ptr + 1);
			*ptr = '\0';
		} else {
			strcpy(cgiargs, "");
		}

		strcpy(filename, ".");
		strcat(filename, uri);
		return 0;
	}
}

void serve_static(int fd, char *filename, int filesize)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXBUF];

    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    printf("Response headers:\n");
    printf("%s", buf);

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

void get_filetype(char *filename, char *filetype)
{
	if(strstr(filename, ".html"))
		strcpy(filetype, "text/html");	
	else if(strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");
	else if(strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpeg");
	else if(strstr(filename, ".mp4"))
		strcpy(filetype, "video/mp4");
	else if(strstr(filename, ".mp3"))
		strcpy(filetype, "audio/mpeg");
	else
		strcpy(filetype, "text/plain");
}

void serve_dynamic(int fd, char *filename, char *cgiargs)
{
	char buf[MAXLINE], *emptylist[] = {NULL};

	sprintf(buf, "HTTP/1.0 200 OK \r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	Rio_writen(fd, buf, strlen(buf));

	if(Fork() == 0) {
		setenv("QUERY_STRING", cgiargs, 1);	
		Dup2(fd, STDOUT_FILENO);
		Execve(filename, emptylist, environ);
	}
	Wait(NULL);
}
