#include <stdio.h>

//int fact_while(int n);

/*
int main()
{
	int r = fact_while(5);
	printf("%d\n", r);
}
*/
int fact_while(int n)
{
	int result = 1;
	while(n > 1) {
		result *= n;
		n--;
	}
	return result;
}
