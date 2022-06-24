#include "ds.h"

/*
	Binary search 
	: 반드시 data 가 sorting 되어있어야 함.

		Worst case : log(N)     (*) except sorting!

	1. While (size of interval > 0)
		1.1 Find the median value on this interval
		1.2 if(key == median) return that index
		1.3 if(median < key) select the right interval and go to step  1.
		1.4 Else select the left interval and go to step 1.

	2. If the size of interval is 0, then key is not here.
		
		data 가 너무 조밀하다면 성능이 떨어진다 -> 개선가능

*/

int bi_search(int key, int* a, int N)
{
	int mid;
	int left = 0; int right = N - 1;
	while (right >= left) {
		mid = (right + left) / 2;
		if (key == a[mid]) return mid;
		if (key < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int bi_insert(int key, int* a, int* N)
{
	int p = 0; int i;
	while (key > a[p] && p < *N) p++; //들어갈 자리 탐색
	for (i = *N; i > p; i--)
		a[i] = a[i - 1]; // 뒤에 다 밀기.
	a[p] = key; // 빈자리에 넣기.
	(*N)++; // 배열 크기 하나 증가.

	return p;
}
int bi_delete(int key, int* a, int* N)
{
	int p;
	int i;
	if (*N > 0)
	{
		if ((p = bi_search(key, a, *N)) < 0) return -1; // searching 못하면 fail
		// searching 되면 p = key 의 position
		for (i = p + 1; i < *N; i++)
			a[i - 1] = a[i]; // 앞으로 밀기
		(*N)--;
		return p;
	}
	return -1;
}
int bii_search(int key, int* a, int N) // modified binary search
{
	int mid;
	int left = 0;
	int right = N - 1;
	while (right >= left)
	{
		mid = left + (float)(key - a[left]) * (right - left) / (a[right] - a[left]);
		if (key == a[mid]) return mid; // find key.
		if (key < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1; // failed searching
}

int gen_bi_search(void* key, void* base, int nelem, int width, FCMP fcmp)
{
	void* temp = malloc(width);
	memcpy(temp, key, sizeof(width));
	int mid, left = 0, right = nelem - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (fcmp(BASE(mid), temp) < 0) left = mid + 1;
		else if (fcmp(BASE(mid), temp) == 0) return mid;
		else right = mid - 1;
	}
	return -1;

}

int gen_bi_insert(void* key, void* base, int *nelem, int width, FCMP fcmp)
{
	void* t = malloc(sizeof(width));
	memcpy(t, key, sizeof(width));
	int p = 0;
	int i;
	while (p < *nelem && fcmp(key, BASE(p)) > 0) p++;
	for (i = *nelem; i > p; i--)
		memcpy(BASE(i), BASE(i - 1), sizeof(width));
	memcpy(BASE(p), t, sizeof(width));
	(*nelem)++;
	return p;
}
int gen_bi_delete(void* key, void* base, int *nelem, int width, FCMP fcmp)
{
	void* t = malloc(sizeof(width));
	memcpy(t, key, width);
	int p = 0, i;
	if((p = gen_bi_search(t, base, *nelem, width, fcmp)) < 0 ) return -1;
	for (i = p + 1; i < *nelem; i++)
		memcpy(BASE(i - 1), BASE(i), sizeof(width));
	(*nelem)--;
	return p;
}
