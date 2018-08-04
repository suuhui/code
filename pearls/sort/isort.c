#include <stdio.h>

void isort1(int *arr);
void isort2(int *arr);

int main()
{
	int arr[] = {8,3,5,2,5,6,1};
	int n = 7;
	int i;
	isort1(arr);
	for(i=0; i<n; i++){
		printf("%d ", arr[i]);	
	}
	printf("\n");
}

void isort1(int *arr)
{
	int i,j,t;
	int n = 7;
	int count = 0;
	for(i=1; i<n; i++) {
		printf("i is :%d and arr[%d] is : %d\n", i, i,arr[i]);
		for(j=i; j>0 && arr[j-1] > arr[j]; j--) {
			count++;
			t = arr[j-1];
			arr[j-1] = arr[j];
			arr[j] = t;
			printf("#### j is :%d and arr[%d] is : %d\n", j, j, arr[j]);
		}
	}
	printf("count : %d\n", count);
}

void isort2(int *arr)
{
	int i,j,t;
	int count = 0;
	int n = 7;
	for(i=1; i<n; i++){
		t = arr[i];
		for(j=i; j>0 && arr[j-1] > t; j--) {
			count++;
			arr[j] = arr[j-1];
		}
		arr[j] = t;
	}
	printf("count : %d\n", count);
}

