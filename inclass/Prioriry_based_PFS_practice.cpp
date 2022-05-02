#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct _node {
	int vertex;
	int weight;
	struct _node* next;
}node;

#define MAX_NODE 100
#define UNSEEN -(INT_MAX)

int check[MAX_NODE] = { 0 };
int parent[MAX_NODE];

int heap[MAX_NODE];
int nheap;

node* head, * tail;
node* GL[MAX_NODE];

FILE* fp;

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void visit(int i) {
	printf(" %c 를 방문함...\n", int2name(i));
}

void pq_init() {
	nheap = 0;
}

void upheap(int h[], int k) {
	int v;
	v = h[k];
	while (check[h[k / 2]] < check[v] && k/2>0) {
		h[k] = h[k / 2];
		k /= 2;
	}
	h[k] = v;
}
void downheap(int h[], int k) {
	int i, v;
	v = h[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap && check[h[i]] < check[h[i + 1]])i++;
		if (check[h[i]] > check[v]) {
			h[k] = h[i];
			k = i;
		}
		else {
			break;
		}
	}
	h[k] = v;
}
int pq_extract(int h[]) {
	int t = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return t;
}
int pq_empty() {
	return (nheap == 0);
}
void adjust_heap(int h[]) {
	int k;
	for (k = nheap; k >= 1; k--) {
		downheap(h, k);
	}

}
int pq_update(int h[], int v, int p) {
	if (check[v] == UNSEEN) {
		h[++nheap] = v;
		check[v] = p;
		upheap(h, nheap);
		return 1;
	}
	else {
		if (check[v] < p) {
			check[v] = p;
			adjust_heap(h);
			return 1;
		}
		else {
			return 0;
		}
	}
}
void print_heap(int h[]) {
	int i;
	printf("\t\t\tHeap : ");
	for (i = 1; i <= nheap; i++) {
		printf("%c(%d) ", int2name(h[i]), check[h[i]]);
	}
	printf("\r");
}
void shortest_adjlist(node* a[], int start, int V) {
	int i, k;
	node* t;
	pq_init();
	for (i = 0; i < V; i++) {
		check[i] = UNSEEN;
		parent[i] = 0;
	}

	i = start;
	if (check[i] == UNSEEN) {
		parent[i] = -1;
		pq_update(heap, i, 0);
		while (!pq_empty()) {
			print_heap(heap);
			k = pq_extract(heap);
			visit(k);
			check[k] = -check[k];
			for (t = a[k]; t != NULL; t = t->next) {
				if (check[t->vertex] < 0) {
					if (pq_update(heap, t->vertex, -t->weight - check[k])) {
						parent[t->vertex] = k;
					}
				}
			}
		}

	}


}
void input_adjlist(node* a[], int* V, int* E) {
	int k, w;
	
	fp = fopen("graph.txt", "rt");
	if (fp == NULL) {
		printf("Failed\n");
		return;
	}
	fscanf(fp, "%d %d", V, E);

	for (k = 0; k < *V; k++) {
		a[k] = NULL;
	}
	char vertex[3];
	int i, j;
	node* t;
	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s %d", vertex, &w);
		i = vertex[0] - 'A';
		j = vertex[1] - 'A';

		t = (node*)malloc(sizeof(node));
		t->vertex = j;
		t->weight = w;
		t->next = a[i];
		a[i] = t;

		t = (node*)malloc(sizeof(node));
		t->vertex = i;
		t->weight = w;
		t->next = a[j];
		a[j] = t;
	}
	fclose(fp);
}
void print_parent(int parent[], int V) {
	int i;
	printf("\n< Parent Node >\n");
	for (i = 0; i < V; i++) {
		printf("%2c ", int2name(i));
	}
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("---");
	}
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%2c ", int2name(parent[i]));
	}
}

int main() {
	int V, E;
	input_adjlist(GL, &V, &E);
	shortest_adjlist(GL, 0, V);
	print_parent(parent, V);
}