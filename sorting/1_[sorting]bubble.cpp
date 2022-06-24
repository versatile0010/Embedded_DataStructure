#include "ds.h"

void bubble_sort(int* a, int N)
{
	int i, j, t;
	printf("bubble sorting start\n");
	//print_arr(a, N);
	//printf("===============================\n");
	for (i = 0; i < N - 1; i++)
	{
		for (j = 1; j < N - i; j++)
		{
			//print_arr(a, N);
			//printf("===============================\n");
			if (a[j - 1] > a[j])  // descending : a[j-1] < a[j]
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
				printf("swap!\n");
			}
		}
	}
	//print_arr(a, N);
	//printf("===============================\n");
}

/*
Generalization of bubble sorting
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
void gen_bubble_sort(void* base, int nelem, int width,
	int (*fcmp)(const void*, const void*))
{
	int i, j;
	void* temp = malloc(width);
	for (i = 0; i < nelem - 1; i++)
	{
		for (j = 1; j < nelem - i; j++)
		{
			if (fcmp((char*)base + (j - 1) * width, (char*)base + j * width) > 0)
			{
				//swap
				memcpy(temp, (char*)base + (j - 1) * width, width);
				memcpy((char*)base + (j - 1) * width, (char*)base + j * width, width);
				memcpy((char*)base + j * width, temp, width);
			}
		}
	}
}