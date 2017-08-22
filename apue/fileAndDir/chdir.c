#include "../apueerr.h"

int main()
{
	char *path;
	int size;
	if(chdir("/tmp") < 0)
		err_sys("chdir failed");
	path = path_alloc(&size);
	if(getcwd(path, size) == NULL)
		err_sys("getcwd failed");
	
	printf("cwd = %s\n", path);
	exit(0);
}
