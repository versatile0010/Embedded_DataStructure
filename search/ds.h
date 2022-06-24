#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h> // for memcpy 
typedef int(*FCMP)(const void*, const void*);

#define MAX 100
#define BASE(i)  ((char*)base + (i)*width)
#define LEN 5

typedef struct _card {
	int no; // student_id
	char name[20];
}card;

typedef struct _student {
	char id[20];
	char name[20];
}student;

typedef struct _node {
	struct _node* next;
}node;

typedef struct double_node {
	int key;
	struct double_node* left;
	struct double_node* right;
}double_node;

// utility
void print_arr(int* a, int N, int start);
int intcmp(const void* a, const void* b);
int char_cmp(const void* a, const void* b);
int float_cmp(const void* a, const void* b);
int double_cmp(const void* a, const void* b);
int card_cmp(const void* a, const void* b);
int id_cmp(const void* a, const void* b);
int name_is_start_with_k(const char* a);
int name2int(char c);
char int2name(int i);


void read_file(int* input, int height, int width, const char* filename);

// stack
void init_stack();
int push(int t);
int pop();
int is_stack_empty();

//bubble sort O(N^2)
void bubble_sort(int* a, int N);
void gen_bubble_sort(void* base, int nelem, int width,
	int (*fcmp)(const void*, const void*));

//select sort O(N^2)
void select_sort(int* a, int N);
void gen_select_sort(void* base, int nelem, int width,
	int (*fcmp)(const void*, const void*));

//insert sort O(N^2)
void insert_sort(int* a, int N);
void indirect_insert_sort(int* a, int* index, int N);
void gen_insert_sort(void* base, int nelem, int width,
	int(*fcmp)(const void*, const void*));
void gen_indirect_insert_sort(void* base, int* index, int nelem, int width,
	int(*fcmp)(const void*, const void*));

//shell sort O(N^1.25)
void shell_sort(int* a, int N);
void modified_shell_sort(int* a, int N);
void indirect_shell_sort(int* a, int* index, int N);
void gen_shell_sort(void* base, int nelem, int width,
	int(*fcmp)(const void*, const void*));

//median filtering
void median_filtering(int* input, int* output, int height, int width);

//quick sorting O(NlogN)
void quick_sort1(int* a, int N);
void quick_sort_nr(int* a, int N);
void quick_sort2(int* a, int N);
void quick_sort3(int* a, int N);
void gen_quick_sort(void* base, int nelem, int width, int(*fcmp)(const void*, const void*));

//Heap sorting O(NlogN)
void upheap(int* a, int k);
void downheap(int* a, int N, int k);
void insert(int* a, int* N, int v);
int extract(int* a, int* N);
void heap_sort_top_down(int* a, int* heap, int N);
void heap_sort_bottom_up(int* a, int N);
void print_heap(int h[], int nh);

//Binary Search O(logN) -> except sorting
int bi_search(int key, int* a, int N);
int bi_insert(int key, int* a, int* N);
int bi_delete(int key, int* a, int* N);
int bii_search(int key, int* a, int N);

int gen_bi_search(void* key, void* base, int nelem, int width, FCMP fcmp);
int gen_bi_insert(void* key, void* base, int nelem, int width, FCMP fcmp);
int gen_bi_delete(void* key, void* base, int nelem, int width, FCMP fcmp);

//Sequential Search 
int seq_search(int key, int* a, int* num);
int seq_insert(int key, int* a, int* num);
int seq_delete(int key, int* a, int* num);
int seq_f_search(int key, int* a, int* num);

int lv_search(void* key, void* base, int* num, int width, FCMP fcmp);
int lv_insert(void* key, void* base, int* num, int width, FCMP fcmp);
int lv_delete(void* key, void* base, int* num, int width, FCMP fcmp);
int lfv_search(void* key, void* base, int* num, int width, FCMP fcmp);

void init_list(node** p);
void* llv_search(void* key, node* base, int* num, int width, FCMP fcmp, int* index = NULL);
void* llv_insert(void* key, node* base, int* num, int width, FCMP fcmp);
void* llv_delete(void* key, node* base, int* num, int width, FCMP fcmp, int* index = NULL);

// Binary Tree search
double_node* bti_search(int key, double_node* base, int* num);
double_node* bti_insert(int key, double_node* base, int* num);
double_node* bti_delete1(int key, double_node* base, int* num);
double_node* bti_delete(int key, double_node* base, int* num);

void bti_sort(double_node* p, int* a, int* index);
double_node* _balance(int N, int* a, int* index);
void btiprint(double_node* p);