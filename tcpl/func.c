#include <stdio.h>
#include <math.h>

int atoi(char *s);
int htoi(char *s);

int main(int argc, char *argv[])
{
	char *s = "123";
	int n = atoi(s);
	printf("%d\n", n);
}

int atoi(char *s)
{
	int n = 0;
	int i = 0;
	for(; s[i] >= '0' && s[i] <='9'; ++i) {
		n = n * 10 + (s[i] - '0');
	}
	return n;
}

int htoi(char *s)
{
	
}

