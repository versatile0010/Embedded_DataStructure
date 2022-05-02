
/*

	< Dijkstra Algorithm >

		Start노드만 하나 넣어주면 모든 노드까지 걸리는 최단거리를 모두 구해준다.

	Adjacency Matrix 사용
		-	나와의 가중치는 0 으로 둔다.
		-	직접적으로 연결되지 않은 노드의 가중치는 Max로 둔다.

	Procedure :

	시작정점 s; 모든 노드의 부모는 시작정점으로 둔다.

	for(모든정점 x에 대해서) {
		distance[x] = 간선(s, x)의 가중치
		x의 부모는 s로 둔다.
	}

	while(체크가 안된 정점이 남아 있을 동안) {
		x = s에서 가장 가까운 정점;
		정점 x를 체크함;
		for(간선(x, y)가 존재하고 체크되지 않은 모든 정점 y에 대하여){
			d = distance[x] + 간선(x, y)의 가중치;
			if(d < distance[y]) {
				distance[y] = d;
				y의 부모는 x;
			}
		}
	}
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE 100
#define Jinf 1000

int check[MAX_NODE];
int parent[MAX_NODE];
int distance[MAX_NODE];

int GM[MAX_NODE][MAX_NODE];

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}

void print_distance(int distance[], int s, int V) {
	int i;

	for (i = 0; i < V; i++) {
		printf("%4d ", distance[i]);
	}
	printf("\n");

}


void finput_adjmatrix(int a[][MAX_NODE], int* V, int* E, FILE* fp) {
	char vertex[3];
	int i, j, w, k;
	printf("\nInput number of node & edge\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = Jinf;
	for (i = 0; i < *V; i++)
		a[i][i] = 0;

	for (k = 0; k < *E; k++) {
		printf("\nInput two node consist of edge -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		
		a[i][j] = w;
		a[j][i] = w;
	}
}

void dijkstra(int a[][MAX_NODE], int s, int V) {
	int x = 0, y, d;
	int i, checked = 0;
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x];
		if (x != s)parent[x] = s;
	}
	check[s] = 1;
	checked++;

	printf("*"); print_distance(distance, s, V);
	while (checked < V) {
		x = 0;
		while (check[x])x++;
		for (i = x; i < V; i++)
			if (check[i] == 0 && distance[i] < distance[x])x = i;
		check[x] = 1;
		checked++;
		for (y = 0; y < V; y++) {
			if (x == y || a[x][y] >= Jinf || check[y])continue;
			d = distance[x] + a[x][y];
			if (d < distance[y]) {
				distance[y] = d;
				parent[y] = x;
			}
		}
		print_distance(distance, s, V);
	}
}

void print_parent(int parent[], int V) {
	int i;
	printf("\nnode : parent\n");
	for (i = 0; i < V; i++) {
		printf("%2c : %2c\n", int2name(i), int2name(parent[i]));
	}
}

int main() {
	int V, E;
	FILE* fp;
	fp = fopen("graph.txt", "rt");
	finput_adjmatrix(GM, &V, &E, fp);
	
	int i;
	printf("\n\n");
	for (i = 0; i < V; i++) {
		printf("%4c ", int2name(i));
	}
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("---- ");
	}
	printf("\n");


	dijkstra(GM, 5, V);

	print_parent(parent, V);

}