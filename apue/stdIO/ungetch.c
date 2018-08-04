#include "../apueerr.h"

int main()
{
	int sum = 0;
	int num;
	char ch;
	while(scanf("%d", &num) == 1){
		sum += num;
		while((ch = getchar()) == ' ');
		if(ch == '\n')
			break;
		ungetc(ch, stdin);
	}
	printf("sum is %d\n", sum);
	printf("last char is %c\n", ch);
	exit(0);
}
