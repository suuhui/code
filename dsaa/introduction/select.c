#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 1000

int randint(int, int);

int main()
{
	int arr[MAX];
	int i;
	int r = 0; //rand int;
	int t = 0; //template number, for exchange;
	int mid = MAX / 2; // 
	for(i=0; i<MAX; i++){
		printf("%d\n", i);
		arr[i] = i;
	}

	for(i=0; i<MAX; i++){
		r = randint(i, MAX);
		printf("%d\n", r);
		t = arr[i];
		arr[i] = arr[r];
		arr[r] = t;
	}

	for(i=0; i<MAX; i++){
		printf("%d\n", arr[i]);
	}
}

int randint(int l, int u)
{
	srand(time(0));
	return (int)(rand()%(u - l + 1) + l);
}

