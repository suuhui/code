#include <stdio.h>
#include "../func.c"

#define M 21
#define MAX 1000

void swap(int *tree, int i, int j);
void hsort(int *tree, int n);
void siftup(int *tree, int n);
void siftdown(int *tree, int n);

int main()
{
	int i, tree[M] = {12,23,23,76,3,686,2,43,1,78,89,60,30,70,68,489,40,9,11,12,34};
	
	hsort(tree, M);
	for(i=1; i<M; i++)
		printf("%d\n", tree[i]);
	printf("\n");
}

void hsort(int * tree, int n)
{
	int i;
	for(i=2; i<n; i++)
		siftup(tree, i);
	
	/* note: n is 21, when ergodic array from top ,init i=n-1 */
	for(i=n-1; i>1; i--) {
		swap(tree, 1, i);
		siftdown(tree, i-1);
	}
}

void siftup(int *tree, int n)
{	
	int i = n, p = i / 2;
	while(tree[p] > tree[i] && i != 1) {
		swap(tree, p, i);
		i = p;
		p = i / 2;
	}
}

void siftdown(int *tree, int n)
{
	int i = 1;
	int c;
	while(1) {
		c = 2 * i;
		if (c > n)
			break;
		if(c + 1 <= n && tree[c] > tree[c+1])
			c++;
		if(tree[c] > tree[i])
			break;
		swap(tree, c, i);
		i = c;
	}
}

void swap(int *tree, int i, int j)
{
	}
	int t;
	t = tree[i];
	tree[i] = tree[j];
	tree[j] = t;
}

