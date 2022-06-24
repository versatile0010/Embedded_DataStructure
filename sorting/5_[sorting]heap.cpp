#include "ds.h"

/*
		Heap(Priority Queue) Sorting  :  O(nlogn)
		Ground rule : parent's value > child's value


		(*) parent node �� index �� j �̸� left child node : 2*j , rgiht child node : 2*j + 1
*/

void upheap(int* a, int k)
{
	int v;
	v = a[k];
	a[0] = INT_MAX; // �� �뵵�� ����� ū ��
	while (a[k / 2] <= v) // �θ��� ���� ���� child �� a[k] ���� �۴ٸ� a[k] �� level �� �ø�
	{
		a[k] = a[k / 2]; // parent �� ����
		k /= 2;
	}
	a[k] = v;
}
void downheap(int* a, int N, int k)
{
	int i;
	int v;
	v = a[k];
	while (k <= N / 2) //internal node �� Ž��
	{ 
		i = k << 1; // i = k * 2 
					// i �� k �� child �ε���
		if (i < N && a[i] < a[i + 1]) i++; // left child �� right child ���� �۴ٸ� right child ����
		if (v >= a[i]) break;
		a[k] = a[i]; 
		k = i;
	}
	a[k] = v;
}

void insert(int* a, int* N, int v) // ���ο� ��带 ����
{
	a[++(*N)] = v; // ���� �ְ�
	upheap(a, *N); // ������
}

int extract(int* a, int* N) // root node �� extract
{
	int v = a[1]; // pick root node
	a[1] = a[(*N)--]; // replace
	downheap(a, *N, 1); 

	return v;
}

void heap_sort_top_down(int* a, int* heap, int N) // top - down ��� heap sorting
{
	int i;
	int hn = 0; // hn : length of heap

	for (i = 1; i <= N; i++)
		insert(heap, &hn, a[i-1]); // heap �� �ְ�
	for (i = hn; i >= 1; i--)
		a[i-1] = extract(heap, &hn); // extract �Ͽ� �ٽ� ����
}


void heap_sort_bottom_up(int* a, int N) // bottom - up ��� heap sorting
{
	int k, t;
	for (k = N / 2; k >= 1; k--) // internal node �� Ž��
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
	for (int i = 1; i <= nh; i++) // 1���� ���
		printf("%d ",h[i]);
}
