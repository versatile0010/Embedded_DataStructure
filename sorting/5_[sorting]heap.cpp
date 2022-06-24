#include "ds.h"

/*
		Heap(Priority Queue) Sorting  :  O(nlogn)
		Ground rule : parent's value > child's value


		(*) parent node 의 index 가 j 이면 left child node : 2*j , rgiht child node : 2*j + 1
*/

void upheap(int* a, int k)
{
	int v;
	v = a[k];
	a[0] = INT_MAX; // 비교 용도로 사용할 큰 값
	while (a[k / 2] <= v) // 부모의 값이 현재 child 인 a[k] 보다 작다면 a[k] 의 level 을 올림
	{
		a[k] = a[k / 2]; // parent 는 내림
		k /= 2;
	}
	a[k] = v;
}
void downheap(int* a, int N, int k)
{
	int i;
	int v;
	v = a[k];
	while (k <= N / 2) //internal node 만 탐색
	{ 
		i = k << 1; // i = k * 2 
					// i 는 k 의 child 인덱스
		if (i < N && a[i] < a[i + 1]) i++; // left child 가 right child 보다 작다면 right child 선택
		if (v >= a[i]) break;
		a[k] = a[i]; 
		k = i;
	}
	a[k] = v;
}

void insert(int* a, int* N, int v) // 새로운 노드를 삽입
{
	a[++(*N)] = v; // 끝에 넣고
	upheap(a, *N); // 재조정
}

int extract(int* a, int* N) // root node 를 extract
{
	int v = a[1]; // pick root node
	a[1] = a[(*N)--]; // replace
	downheap(a, *N, 1); 

	return v;
}

void heap_sort_top_down(int* a, int* heap, int N) // top - down 방식 heap sorting
{
	int i;
	int hn = 0; // hn : length of heap

	for (i = 1; i <= N; i++)
		insert(heap, &hn, a[i-1]); // heap 에 넣고
	for (i = hn; i >= 1; i--)
		a[i-1] = extract(heap, &hn); // extract 하여 다시 저장
}


void heap_sort_bottom_up(int* a, int N) // bottom - up 방식 heap sorting
{
	int k, t;
	for (k = N / 2; k >= 1; k--) // internal node 만 탐색
		downheap(a, N, k);
	N--;
	while (N >= 1) //extraction and downheap
	{
		t = a[0]; // Root <- max value
		a[0] = a[N];
		a[N] = t;

		downheap(a, --N, 0);
	}
}

void print_heap(int h[], int nh)
{
	printf("\n");
	for (int i = 1; i <= nh; i++) // 1부터 출력
		printf("%d ",h[i]);
}
