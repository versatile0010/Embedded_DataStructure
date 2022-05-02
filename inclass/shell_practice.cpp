//
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#include<string.h>
//
//void shell_sort2(int*a, int N){
//	int i, j, t, v, h;
//	for (h = N / 2; h >= 0; h = (h - 1) / 3) {
//		if (h == 0)h = 1;
//		for (i = 0; i < h; i++) {
//			for (j = i + h; j < N; j += h) {
//				v = a[j];
//				t = j;
//				while (t - h >= 0 && a[t - h] > v) {
//					a[t] = a[t - h];
//					t -= h;
//				}
//				a[t] = v;
//			}
//		}
//		if (h == 1)break;
//	}
//}
//void shell_sort(int* a, int N) {
//	int i, j, h, t, v;
//	for (h = N / 2; h > 0; h /= 2) {
//		for (i = 0; i < h; i++) {
//			for (j = i + h; j < N; j += h) {
//				v = a[j];
//				t = j;
//				while (t - h >= 0 && a[t - h] > v) {
//					a[t] = a[t - h];
//					t -= h;
//				}
//				a[t] = v;
//			}
//		}
//	}
//}
//
//void indirect_shell_sort(int* a, int* index, int N) {
//	int i, j, t, h, v;
//	for (i = 0; i < N; i++)
//		index[i] = i;
//	for (h = N / 2; h > 0; h /= 2) {
//		for (i = 0; i < h; i++) {
//			for (j = i + h; j < N; j += h) {
//				v = a[j];
//				t = j;
//				while (t - h >= 0 && a[index[t - h]] > v) {
//					index[t] = index[t - h];
//					t -= h;
//				}
//				index[t] = j;
//			}
//		}
//	}
//}
//int int_cmp(const void* a, const void* b) {
//	return (*(int*)a - *(int*)b);
//}
//int char_cmp(const void* a, const void* b) {
//	return (*(char*)a - *(char*)b);
//}
//void gen_shell_sort(void* base, int nelem, int width, int(*fcmp)(const void*, const void*)) {
//	int i, j, h, t;
//	void* v = malloc(width);
//	for (h = nelem / 2; h > 0; h /= 2) {
//		for (i = 0; i < h; i++) {
//			for (j = i + h; j < nelem; j += h) {
//				memcpy(v, (char*)base + j * width, width);
//				t = j;
//				while (t - h >= 0 && fcmp((char*)base + (t - h) * width, v) > 0) {
//					memcpy((char*)base + t * width, (char*)base + (t - h) * width, width);
//					t -= h;
//				}
//				memcpy((char*)base + t * width, v, width);
//			}
//		}
//	}
//	free(v);
//}
//
//#define MAX 100
//
//int main() {
//	srand((unsigned)time(NULL));
//	int a[MAX];
//	int index[MAX];
//	int i;
//	for (i = 0; i < MAX; i++) {
//		a[i] = rand() % MAX;
//	}
//	for (i = 0; i < MAX; i++) {
//		printf("%4d ", a[i]);
//	}
//	printf("\n\n");
//
//	gen_shell_sort(a, MAX, sizeof(int), int_cmp);
//
//	for (i = 0; i < MAX; i++) {
//		printf("%4d ", a[i]);
//		//printf("%4d ", a[index[i]]);
//
//	}
//}