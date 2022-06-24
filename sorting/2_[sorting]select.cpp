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


//nelem : 데이터 개수, width : sizeof(element type)
		/*
		(char*) 으로 casting 하는 이유
		: 컴파일러가 배열 a[y] 에서 a 가 int* type 인 것을 확인하면
		a[y] -> *(a + y * sizeof(int)) 로 치환한다.
		그러면, a[y] 는 *(type)((char*)a + y * width) 로 사용하자.
		(*) 1 byte 인 char* 을 사용하면 sizeof(char) = 1 이므로
		width 에 1을 곱해도 의도대로 동작한다.
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
