#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void insert_sort(int* a, int N) {
	int i, j, t;
	for (i = 0; i < N; i++) {
		t = a[i];
		j = i;
		while (j > 0 && a[j - 1] > t) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = t;
	}
}

void indirect_insert_sort(int* a, int* index, int N) {
	int i, j, t;
	for (i = 0; i < N; i++) {
		index[i] = i;
	}
	for (i = 0; i < N; i++) {
		t = index[i];
		j = i;
		while (j > 0 && a[index[j - 1]] > a[t]) {
			index[j] = index[j - 1];
			j--;
		}
		index[j] = i;
	}
}

int int_cmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}
int char_cmp(const void* a, const void* b) {
	return (*(char*)a - *(char*)b);
}
int float_cmp(const void* a, const void* b) {
	return (*(float*)a - *(float*)b);
}

void gen_insert_sort(void* base, int nelem, int width, int(*fcmp)(const void*, const void*)) {
	int i, j;
	void* t = malloc(width);
	for (i = 0; i < nelem; i++) {
		memcpy(t, (char*)base + i * width, width);
		j = i;
		while (j > 0 && fcmp((char*)base + (j - 1) * width, t) > 0) {
			memcpy((char*)base + (j)*width, (char*)base + (j - 1) * width, width);
			j--;
		}
		memcpy((char*)base + j * width, t, width);
	}
}

void gen_indirect_insert_sort(void* base, int* index, int nelem, int width, int(*fcmp)(const void*, const void*)) {
	int i, j;
	void* t = malloc(width);
	for (i = 0; i < nelem; i++) {
		index[i] = i;
	}

	for (i = 0; i < nelem; i++) {
		memcpy(t, (char*)base + i * width, width);
		j = i;
		while (j > 0 && fcmp((char*)base + (index[j-1]) * width, t) > 0) {
			index[j] = index[j - 1];
			j--;
		}
		index[j] = i;
	}
}

#define MAX 100

int main() {
	srand((unsigned)time(NULL));
	int a[MAX];
	int index[MAX];
	int i;
	for (i = 0; i < MAX; i++) {
		a[i] = rand() % MAX;
	}
	for (i = 0; i < MAX; i++) {
		printf("%4d ", a[i]);
	}
	printf("\n\n");
	gen_indirect_insert_sort(a, index, MAX, sizeof(int), int_cmp);

	for (i = 0; i < MAX; i++) {
		printf("%4d ", a[index[i]]);
	}

}