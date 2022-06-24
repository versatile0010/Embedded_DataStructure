#include "ds.h"

/*
	insertion sorting(삽입 정렬) : O(N^2)
	효율이 좋은 편(base case, half case 일때 빠름)
	Worst case(reverse) 인 경우 select sorting 보다 효율이 떨어진다.

	일상에서 카드를 정렬하는 방법과 같다
*/

void insert_sort(int* a, int N)
{
	int i, j, t;
	printf("insert sort start\n");
	for (i = 1; i < N; i++)
	{
		t = a[i];
		j = i;
		while (j > 0 && a[j - 1] > t)
		{
			//swap
			a[j] = a[j - 1];
			j--;
		}
		a[j] = t;
	}
}
// It's better than insert_sort when we have to  Optimize.
// And often we have to preserve original data.
// In that case, we can use indirect sorting method
// Key idea is sorting index array.
void indirect_insert_sort(int* a, int* index, int N)
{
	int i, j, t;
	printf("indirect insert sort start\n");
	for (i = 0; i < N; i++) index[i] = i;
	for (i = 1; i < N; i++)
	{
		t = index[i];
		j = i;
		while (j > 0 && a[index[j - 1]] > a[t])
		{
			//swap
			index[j] = index[j - 1];
			j--;
		}
		index[j] = i;
	}
}
void gen_insert_sort(void* base, int nelem, int width,
	int(*fcmp)(const void*, const void*))
{
	int i, j;
	void* t = malloc(width);
	printf("(generalized) insert sorting start\n");
	for (i = 0; i < nelem; i++)
	{
		memcpy(t, (char*)base + i * width, width);
		j = i;
		while (j > 0 && fcmp((char*)base + (j - 1) * width, t) > 0)
		{
			memcpy((char*)base + j * width, (char*)base + (j - 1) * width, width);
			j--;
		}
		memcpy((char*)base + j * width, t, width);
	}
}
void gen_indirect_insert_sort(void* base, int* index, int nelem, int width,
	int(*fcmp)(const void*, const void*))
{
	int i, j;
	void* t = malloc(width);
	for (i = 0; i < nelem; i++) {
		index[i] = i;
	}
	printf("(generalized) indirect insert sorting start\n");
	for (int i = 0; i < nelem; i++)
	{
		memcpy(t, (char*)base + i * width, width);
		j = i;
		while (j > 0 && fcmp((char*)base + index[j - 1] * width, t) > 0)
		{
			index[j] = index[j - 1];
			j--;
		}
		index[j] = i;
	}

}