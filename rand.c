#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //rand, srand
#include <time.h> // time

int main()
{
	int n; 
	scanf("%d", &n);
	int* arr = (int*)calloc(7, sizeof(int));
	if (arr == NULL)
	{
		printf("error!\n");
		return 0;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		int temp = rand()%6+1;
		arr[temp]++;
	}
	for (int i = 1; i <= 6; i++)
	{
		printf("arr[%d] = %d \n", i, arr[i]);
	}

	free(arr);
	return 0;
}