#include "../apueerr.h"

static void charatatime(char *);

int main(void)
{
	pid_t pid;
	if((pid = fork()) < 0){
		err_sys("fork error");	
	} else if(pid == 0) {
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");	
	}
}

static void charatatime(char *s)
{
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for(ptr = s; (c = *ptr++) != 0; )
		putc(c, stdout);
}
