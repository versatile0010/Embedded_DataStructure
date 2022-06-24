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

//nelem : 데이터 개수, width : sizeof(element type)
		/*
		(char*) 으로 casting 하는 이유
		: 컴파일러가 배열 a[y] 에서 a 가 int* type 인 것을 확인하면
		a[y] -> *(a + y * sizeof(int)) 로 치환한다.
		그러면, a[y] 는 *(type)((char*)a + y * width) 로 사용하자.
		(*) 1 byte 인 char* 을 사용하면 sizeof(char) = 1 이므로
		width 에 1을 곱해도 의도대로 동작한다.
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