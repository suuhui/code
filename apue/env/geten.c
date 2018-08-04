#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char *key = "PWD";
	char *val;

	int i = setenv("MY", "name", 1);
	val = getenv("PATH");
	printf("%s\n", val);
	return 0;
}
