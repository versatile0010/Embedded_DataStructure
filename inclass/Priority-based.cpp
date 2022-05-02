
/*
	PFS / Kruskal�� �����
	(Spanning Tree ���)

		" ���� �ּҺ���� �����ΰ�?? "

	< Priority-based Alogorithm >
	
		�� ��尣�� �ִܰŸ��� ���ϱ� ����
		������ ����ġ ���� ������� �켱���� ���� ( PFS�� ��¦ ���� )

	< Dijkstra Algorithm >

		Start��常 �ϳ� �־��ָ� ��� ������ �ɸ��� �ִܰŸ��� ��� �����ش�.
		Adjacency Matrix ���
		-	������ ����ġ�� 0 ���� �д�.
		-	���������� ������� ���� ����� ����ġ�� Max�� �д�.

*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE 100
#define UNSEEN -(INT_MAX)

int check[MAX_NODE];
int parent[MAX_NODE];
int heap[MAX_NODE];
int nheap;

typedef struct _node {
	int weight;
	int vertex;
	struct _node* next;
}node;

node* GL[MAX_NODE];

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void visit(int i) {
	printf("* %c��°�� �湮�� *\n", int2name(i));
}
void upheap(int h[], int k) {
	int v;
	v = h[k];
	while (check[h[k / 2]] <= check[v] && k / 2 > 0) {
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
		if (i < nheap && check[h[i]] < check[h[i + 1]])
			i++;
		if (check[v] >= check[h[i]]) break;
		h[k] = h[i];
		k = i;
	}
	h[k] = v;
}
void adjust_heap(int h[], int n) {
	int k;
	for (k = nheap; k >= 1; k--)
		downheap(h, k);
}
int pq_empty() {
	if (nheap == 0)
		return 1;
	return 0;
}
int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;

}
void pq_init() {
	nheap = 0;
}
void print_heap(int h[]) {
	int i;
	printf("\n");
	for (i = 1; i <= nheap; i++)
		printf("%c:%d ", int2name(h[i]), check[h[i]]);
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
			adjust_heap(h, nheap);
			return 1;
		}
		else
			return 0;
	}
}

void finput_adjlist(node* a[], int* V, int* E, FILE* fp) {
	char vertex[3];
	int i, j, w;
	node* t;
	printf("\nInput number of node & edge\n");
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++)
		a[i] = NULL;

	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->weight = w;
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;

		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->weight = w;
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}

void shortest_adjlist(node* g[], int start, int V) {
	int i;
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
			i = pq_extract(heap);	
			visit(i);				
			check[i] = -check[i];	
			for (t = g[i]; t != NULL; t = t->next) {	
				if(check[t->vertex] < 0)				
					if (pq_update(heap, t->vertex, -t->weight - check[i])) {
						parent[t->vertex] = i;	
					}
			}
		}
	}
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

void print_cost(int check[], int V) {
	int i;
	int sum = check[V-1];
	printf("\nminimum cost : ");
	printf("%d\n\n", sum);
}

int main() {

	int V, E;
	FILE* fp;
	fp = fopen("graph.txt", "rt");
	finput_adjlist(GL, &V, &E, fp);

	shortest_adjlist(GL, 0, V);

	print_parent(parent,V);
	print_cost(check, V);
}