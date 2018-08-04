#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *getLine()
{
	char buf[8];
	char *result;
	gets(buf);
	result = malloc(strlen(buf));
	strcpy(result, buf);

	return result;
}

int main()
{
	char *s;
	s = getLine();
	printf("%s\n", s);
}
