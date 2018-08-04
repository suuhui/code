#include "../apueerr.h"
#include <dirent.h>
#include <limits.h>

/* function type that is called for each filename */
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int ftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
int main(int argc, char **argv)
{
	int ret;
	if(argc != 2)
		err_quit("Usage: ftw.exe <start-filename>\n");
	
	ret = ftw(argv[1], myfunc);
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if(ntot == 0)
		ntot = 1;
	printf("regular   files = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
	printf("directory fhles = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
	printf("block     files = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
	printf("char specials   = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
	printf("FIFOS     files = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("symbolic  files = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
	printf("sockets   files = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
	exit(ret);
}

#define FTW_F    1		/* file */
#define FTW_D    2		/* directory*/
#define FTW_DNR  3      /* directory that can't be read */
#define FTW_NS   4		/* file that we can't stat */

static char *fullpath;

static int ftw(char *pathname, Myfunc *func)
{
	int len;
	fullpath = path_alloc(&len);	/* malloc's for PATH_MAX+1 bytes */
	strncpy(fullpath, pathname, len);
	fullpath[len - 1] = 0;

	return (dopath(func));
}

static int dopath(Myfunc *func)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret;
	char *ptr;

	if(lstat(fullpath, &statbuf) < 0)
		return (func(fullpath, &statbuf, FTW_NS));
	if(S_ISDIR(statbuf.st_mode) == 0)
		return (func(fullpath, &statbuf, FTW_F));

	if((ret = func(fullpath, &statbuf, FTW_D) != 0))
		return ret;

	ptr = fullpath + strlen(fullpath);
	*ptr++ = '/';
	*ptr = 0;

	if((dp = opendir(fullpath)) == NULL)
		return (func(fullpath, &statbuf, FTW_DNR));

	while((dirp = readdir(dp)) != NULL) {
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;
		strcpy(ptr, dirp->d_name);
		if((ret = dopath(func) != 0))
			break;
	}

	ptr[-1] = 0;

	if(closedir(dp) < 0)
		err_ret("cnat't close directory %s", fullpath);

	return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch(type) {
	case FTW_F:
		switch(statptr->st_mode & S_IFMT) {
		case S_IFREG:	nreg++;		break;	
		case S_IFBLK:	nblk++;		break;	
		case S_IFCHR:	nchr++;		break;	
		case S_IFIFO:	nfifo++;	break;	
		case S_IFLNK:	nslink++;	break;	
		case S_IFSOCK:	nsock++;	break;	
		case S_IFDIR:
			err_dump("for S_IFDIR is %s", pathname);
		}
		break;

	case FTW_D:
		ndir++;
		break;
	
	case FTW_DNR:
		err_ret("can't be read dir %s", pathname);
		break;
	
	case FTW_NS:
		err_ret("stat error for %s", pathname);
		break;
	
	default:
		err_dump("unknow type %d for pathname %s", type, pathname);
	}
	
	return 0;
}

