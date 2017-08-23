#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(int l, int u);

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("Usage: ./randint.exe [lower] [upper]\n");
		return (1);
	}
	int t = randint(atoi(argv[1]), atoi(argv[2]));
	printf("rand num is : %d\n", t);
	return 0;
}

int randint(int l, int u)
{
	srand(time(0));
	return (rand() % (u - l + 1)) + l;	
}
