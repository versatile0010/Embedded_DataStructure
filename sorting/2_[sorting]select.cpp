#include "ds.h"

void select_sort(int* a, int N)
{
	int min;
	int min_idx;
	int x, y;
	//printf("selection sort start\n");
	//print_arr(a, N);
	//printf("=========================\n");
	for (y = 0; y < N - 1; y++)
	{
		min_idx = y;
		min = a[y];
		for (x = y + 1; x < N; x++)
		{
			if (min > a[x])
			{
				min = a[x];
				min_idx = x;
			}
		}
		a[min_idx] = a[y]; // swap
		a[y] = min;
		//print_arr(a, N);
		//printf("=========================\n");
	}
}

/*
Generalization of selection sorting
*/


//nelem : ������ ����, width : sizeof(element type)
		/*
		(char*) ���� casting �ϴ� ����
		: �����Ϸ��� �迭 a[y] ���� a �� int* type �� ���� Ȯ���ϸ�
		a[y] -> *(a + y * sizeof(int)) �� ġȯ�Ѵ�.
		�׷���, a[y] �� *(type)((char*)a + y * width) �� �������.
		(*) 1 byte �� char* �� ����ϸ� sizeof(char) = 1 �̹Ƿ�
		width �� 1�� ���ص� �ǵ���� �����Ѵ�.
		*/
void gen_select_sort(void* base, int nelem, int width, 
						int (*fcmp)(const void*, const void*))
{
	void* min;
	int min_idx;
	int x, y;

	min = malloc(width);
	for (y = 0; y < nelem - 1; y++)
	{
		min_idx = y;
		memcpy(min, (char*)base + y * width, width);
		for (x = y + 1; x < nelem; x++)
		{
			if (fcmp(min, (char*)base + x * width) > 0)
			{
				memcpy(min, (char*)base + x * width, width);
				min_idx = x;
			}
		}
		memcpy((char*)base + min_idx * width, (char*)base + y * width, width);
		memcpy((char*)base + y * width, min, width);
	}
	free(min);
}
