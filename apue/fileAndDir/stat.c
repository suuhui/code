#include "../apueerr.h"

int main()
{
	struct stat st;
	stat("test.txt", &st);

	if(S_ISREG(st.st_mode))
		printf("regular file\n");
	
	return 0;
}
