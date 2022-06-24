#include "ds.h"

void print_arr(int* a, int N, int start)
{
	for (int i = start; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int intcmp(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}
int char_cmp(const void* a, const void* b) {
	return (*(char*)a - *(char*)b);
}
int float_cmp(const void* a, const void* b) {
	return (*(float*)a - *(float*)b);
}
int double_cmp(const void* a, const void* b) {
	return (*(double*)a - *(double*)b);
}
int card_cmp(const void* a, const void* b){
	return (((card*)a)->no - ((card*)b)->no);
	//return (*(card*)a).no - (*(card*)b).no;
}

int name_is_start_with_k(const char* a) {
	if (*a == 'k' || *a == 'K')
		return 1;
	else
		return 0;
}

int id_cmp(const void* a, const void* b) {
	student* aa = (student*)a;
	student* bb = (student*)b;
	return strcmp(aa->id, bb->id);
}

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}

void read_file(int* input, int height, int width, const char* filename) {
	int x, y;
	FILE* fp;
	fp = fopen(filename, "rt");

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fscanf(fp, "%d", &input[y * width + x]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}



/*  STACK (Array based */

#define STACK_MAX 1000
int top;
int stack[STACK_MAX];
void init_stack()
{
	top = -1;
}
int push(int t)
{
	if (top >= STACK_MAX - 1)
	{
		printf("Stack Overflow!!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}
int pop()
{
	if (top < 0)
	{
		printf("Stack Underflow!!\n");
		return -1;
	}
	return stack[top--];
}
int is_stack_empty()
{
	return (top < 0) ? 1 : 0;
}
