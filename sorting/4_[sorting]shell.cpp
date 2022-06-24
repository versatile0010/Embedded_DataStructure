#include "ds.h"

/*
	Shell sorting, O(N^1.25)
	- insertion sorting ( using interval )
	- 정해놓은 interval 에 따라 정렬되면서, interval 의 크기를 줄여나간다.
	- interval 이 1 보다 작아지면 stop -> insertion sorting 수행한다.

	- 어느정도 정렬된 배열에 대해서 insertion sorting 의 효율이 좋음을 이용하여
	  성능을 개선한 것이다.
	- reverse 를 sorting 하는 것도 빠르다.

*/

void shell_sort(int* a, int N)
{
	int i, j, k, h, v;
	printf("shell sorting start\n");
	for (h = N / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i + h; j < N; j += h)
			{
				v = a[j];
				k = j;
				while (k > h - 1 && a[k - h] > v)
				{
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
}

void modified_shell_sort(int* a, int N)
{
	printf("modified shell sorting start\n");
	int i, j, k, h, v;
	for (h = N / 2; h >= 0; h = (h - 1) / 3) {
		if (h == 0)h = 1;
		for (i = 0; i < h; i++) {
			for (j = i + h; j < N; j += h) {
				v = a[j];
				k = j;
				while (k > h - 2 && a[k - h] > v) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
		if (h == 1)break;
	}
}

void indirect_shell_sort(int* a, int* index, int N)
{
	int i, j, t, h, v;
	for (i = 0; i < N; i++) index[i] = i;
	for (h = N / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i + h; j < N; j += h)
			{
				v = a[j];
				t = j;
				while (t - h > 0 && a[index[t - h]] > v)
				{
					index[t] = index[t - h];
					t -= h;
				}
				index[t] = j;
			}
		}
	}
}
void gen_shell_sort(void* base, int nelem, int width,
	int(*fcmp)(const void*, const void*)) {
	int i, j, h, t;
	void* v = malloc(width);
	for (h = nelem / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i + h; j < nelem; j += h)
			{
				memcpy(v, (char*)base + j * width, width);
				t = j;
				while (t > h - 1 && fcmp((char*)base + (t - h) * width, v) > 0)
				{
					memcpy((char*)base + t * width, (char*)base + (t - h) * width, width);
					t -= h;
				}
				memcpy((char*)base + t * width, v, width);
			}
		}
		free(v);
	}

}