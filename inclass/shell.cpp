/*
		Shell Sort, big_O notaton : O(N^1.25)
	
		-	Insertion sort�� �⺻������ ������ Interval�� ����Ѵ�.

		-	ũ�Ⱑ N�̸� interval�� h = N/2 �� �����д�. (���ϱ� ����)
		-	Interval�� ���� �����ϸ鼭 interval�� ũ�⸦ ��� ���ݾ� ���δ�.
		-	Interval�� �پ��ٰ� 1�̸��̸� �ߴ��ϰ� Insertion sort ����.

		-	���� ���ĵ� ���� �����Ҷ��� insertion sort�� �ſ� ������.
		-	Reverse�� sort�� �� ������.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void shell_sort(int* a, int N) {
	int i, j, k, h, v;
	for (h = N / 2; h >= 0; h = (h - 1) / 3) {	// h = (h - 1)/3 �� �غ���
		if (h == 0) h = 1;
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
void shell_sort2(int* a, int N) {
	int i, j, k, h, v;
	for (h = N / 2; h > 0; h /= 2) {	// h = (h - 1)/3 �� �غ���
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
	}
}

#define N 300

int main() {
	LARGE_INTEGER freq, start, stop;
	double diff1, diff2;
	QueryPerformanceFrequency(&freq);

	srand((unsigned)time(NULL));
	int a[N];
	int b[N];
//	int index[30];
	int i;
	for (i = 0; i < N; i++) {
		a[i] = rand() % N;
		b[i] = a[i];
	}
	for (i = 0; i < N; i++) {
		printf("%4d", a[i]);
	}
	printf("\n\n");
	QueryPerformanceCounter(&start);
	shell_sort(a, N);
	QueryPerformanceCounter(&stop);
	diff1 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("\n");

	QueryPerformanceCounter(&start);
	shell_sort2(b, N);
	QueryPerformanceCounter(&stop);
	diff2 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n\n");
	for (i = 0; i < N; i++) {
		printf("%4d", a[i]);
	}

	printf("\n\n�ɸ� �ð� : \n\n");
	printf("\th = (h-1)/3 -> %.7lf\n", diff1);
	printf("\th = h/2     -> %.7lf\n\n", diff2);

}