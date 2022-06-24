#include "ds.h"

/*
	Shell sorting, O(N^1.25)
	- insertion sorting ( using interval )
	- ���س��� interval �� ���� ���ĵǸ鼭, interval �� ũ�⸦ �ٿ�������.
	- interval �� 1 ���� �۾����� stop -> insertion sorting �����Ѵ�.

	- ������� ���ĵ� �迭�� ���ؼ� insertion sorting �� ȿ���� ������ �̿��Ͽ�
	  ������ ������ ���̴�.
	- reverse �� sorting �ϴ� �͵� ������.

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