#include <stdio.h>
#include <stdlib.h>

char *inttohex(long a);

char *buf;

int main(int argc, char *argv)
{
	long n;
	printf("please enter a number: ");
	scanf("%ld", &n);

	inttohex(n);
	printf("%s\n", buf);
}

char *inttohex(long a)
{
	int mod = 0;
	int i=0;
	long n;
	
	do {
		mod = a % 16;
		buf[i] = mod < 10 ? mod + '0' : mod - 10 + 'A';
		a = (long)(a / 16);
		i++;
	} while(a != 0);
	buf[i] = '\0';
	return buf;
}
