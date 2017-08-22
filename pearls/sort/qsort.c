#include <stdio.h>

void qsort(int *arr, int l, int u);
void swap(int *arr, int i, int j);

int main()
{
	int arr[] = {5,2,67,3,77,32,64,23,86};
	int n = 9;
	qsort(arr, 0, n);
	int i;
	for(i=0; i<n; i++)
		printf("%d\n", arr[i]);
	printf("\n");
}

void qsort(int *arr, int l, int u)
{
	printf("#############################################\n");
	printf("l is: %d +++ u is: %d\n", l, u);
	if(l >= u)
		return;
	int i=l, j=u, t=arr[l];
	int tmp = 0;
	int k=0;
	while(i <= j) {
		i++;
		while(i<=j && arr[i]<t)
			i++;
		printf("new more than {%d} i is: %d and arr[%d] is: %d\n", t, i, i, arr[i]);
		while(i<=j && arr[j]>t)
			j--;
		printf("new less than {%d} j is: %d and arr[%d] is: %d\n", t, j, j, arr[j]);
		if(i > j)
			break;
		printf("swap i:%d and j:%d\n", i, j);
		swap(arr, i, j);
	}
	swap(arr, l, j);
	printf("-------------------\n");
	for(k=0; k<9; k++)
		printf("%d\n", arr[k]);
	printf("-------------------\n");
	printf("#############################################\n");
	qsort(arr, l, j-1);
	qsort(arr, j+1, u);
}

void swap(int *arr, int i, int j)
{
	int t;
	t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}

