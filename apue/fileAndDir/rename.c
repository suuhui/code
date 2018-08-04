#include "../apueerr.h"

int main(int argc, char **argv)
{
	if(argc != 3)
		err_quit("Usage: rename.exe <oldname> <newname>\n");

	const char *oldname = argv[1];
	const char *newname = argv[2];
	int ret;
	ret = rename(oldname, newname);

	printf("ret is %d\n", ret);
	exit(0);
}
