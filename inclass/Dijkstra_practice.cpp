
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE 100
#define Jinf 1000

FILE* fp;

int check[MAX_NODE] = { 0 };
int parent[MAX_NODE];
int GM[MAX_NODE][MAX_NODE];

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {

	fp = fopen("graph2.txt", "rt");
	if (fp == NULL)
		return;
	fscanf(fp, "%d %d", V, E);

	int i,j;
	for (i = 0; i < *V; i++) {
		for (j = 0; j < *V; j++) {
			a[i][j] = 1000;
		}
	}
	for (i = 0; i < *V; i++)
		a[i][i] = 0;

	int k;
	char vertex[3];
	int weight;
	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s %d", vertex, &weight);
		i = vertex[0] - 'A';
		j = vertex[1] - 'A';
		a[i][j] = weight;
		a[j][i] = weight;
	}
}

void print_bar(int V) {
	int i;
	for (i = 0; i < V; i++) {
		printf("%4c ", i + 'A');
	}
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("---- ");
	}
	printf("\n");
}
void print_distance(int distance[], int V) {
	int i;
	for (i = 0; i < V; i++) {
		printf("%4d ", distance[i]);
	}
	printf("\n");
}

void dijkstra(int a[][MAX_NODE], int s, int V) {
	
	int x, y, checked = 0;
	int distance[MAX_NODE];
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x];
		if(x!=s) parent[x] = s;
	}
	check[s] = 1;
	checked++;
	print_bar(V);
	print_distance(distance, V);
	int i, d;
	while (checked < V) {
		x = 0;
		while (check[x])x++;
		for (i = x; i < V; i++) {
			if (check[i] == 0 && distance[i] < distance[x])x = i;
		}
		check[x] = 1;
		checked++;
		
		for (y = 0; y < V; y++) {
			if (check[y] || a[x][y] >= Jinf)continue;
			d = distance[x] + a[x][y];
			if (distance[y] > d) {
				distance[y] = d;
				parent[y] = x;
			}
		}
		print_distance(distance, V);
	}
}

int main() {

	int V, E;
	input_adjmatrix(GM, &V, &E);
	dijkstra(GM, 0, V);

}