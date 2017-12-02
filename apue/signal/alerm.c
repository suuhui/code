#include "../apueerr.h"

static void sig_alrm(int);

int main()
{
	int n;
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		err_sys("signam(SIGALRM) error");	
	}
	alarm(10);
	for(n=0; n<10; n++)
		;
	sleep(3);
	n = alarm(2);
	printf("%d\n", n);
	sleep(3);
	n = alarm(1);
	printf("%d\n", n);
}

static void sig_alrm(int signo)
{
	printf("alarm signal handle\n");
}
