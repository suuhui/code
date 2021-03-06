#include "../apueerr.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int val;

	if(argc != 2)
		err_quit("Usage: a.out <descriptor#>");
	
	if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		err_sys("fcntl error for fd %d\n", atoi(argv[1]));
	
	/* use mask word O_ACCMODE get access mode bit */
	switch(val & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;

		case O_WRONLY:
			printf("write only");
			break;

		case O_RDWR:
			printf("read write");
			break;

		default:
			err_dump("unknown access mode");
	}

	if(val & O_APPEND)
		printf(", append");
	if(val &O_NONBLOCK)
		printf(", nonblocking");

	#if defined(O_SYNC)
		if(val & O_SYNC)
			printf(", synchronous write");
	#endif
	
	#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
		if(val & O_FSYNC)
			printf(", synchronous writes");
	#endif
	putchar('\n');
	exit(0);
}

/* flags are file status flags to turn on
 * Don't simply use F_SETFD or F_SETFL 
 * You should get flag first, and then modify it, at last
 * set new flag
 */
void set_fl(int fd, int flags)
{
	int val;
	if((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");

	val |= flags; /* turn on flags */

	if(fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}

/*
 * turn of flags
 */
void clr_fl(int fd, int flags)
{
	int val;
	if((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");

	val &= ~flags; /* turn off flags */

	if(fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}
