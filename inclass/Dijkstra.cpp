
/*

	< Dijkstra Algorithm >

		Start��常 �ϳ� �־��ָ� ��� ������ �ɸ��� �ִܰŸ��� ��� �����ش�.

	Adjacency Matrix ���
		-	������ ����ġ�� 0 ���� �д�.
		-	���������� ������� ���� ����� ����ġ�� Max�� �д�.

	Procedure :

	�������� s; ��� ����� �θ�� ������������ �д�.

	for(������� x�� ���ؼ�) {
		distance[x] = ����(s, x)�� ����ġ
		x�� �θ�� s�� �д�.
	}

	while(üũ�� �ȵ� ������ ���� ���� ����) {
		x = s���� ���� ����� ����;
		���� x�� üũ��;
		for(����(x, y)�� �����ϰ� üũ���� ���� ��� ���� y�� ���Ͽ�){
			d = distance[x] + ����(x, y)�� ����ġ;
			if(d < distance[y]) {
				distance[y] = d;
				y�� �θ�� x;
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