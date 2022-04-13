#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define SIZE 15

int input_map[SIZE][SIZE] = {
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,
	0,1,0,0,0,0,1,0,0,0,1,1,0,1,0,
	0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,
	0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,
	0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,
	0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,
	0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,
	0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
	0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,
	0,1,1,1,1,1,0,1,0,0,1,1,0,1,0,
	0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,
	0,1,1,1,0,1,0,1,0,0,0,0,0,1,0,
	0,1,0,0,0,1,0,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,0,0,0,0,0,0
};
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; //세로(row)
int dy[8] = { 0,1, 1, 1, 0,-1,-1,-1 }; //가로(col)

int stack[MAX];
int top;

void init_stack()
{
	top = -1;
}
int push(int t)
{
	if (top >= MAX - 1)
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
int isit_empty()
{
	return (top < 0) ? 1 : 0;
}

void cca(int graph[][SIZE], int x, int y)
{
	int label = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (graph[i][j] == 1)
			{
				init_stack();
				++label;

				push(0);
				push(i);
				push(j);
				while (!isit_empty())
				{
					int adj_y = pop();
					int adj_x = pop();
					int start = pop();

					if (graph[adj_x][adj_y] == 1)
					{
						graph[adj_x][adj_y] = label;

						for (int dir = 0; dir < 8; dir ++ )
						{
							int nx = adj_x + dx[dir];
							int ny = adj_y + dy[dir];

							if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) continue;
							if (graph[nx][ny] == 1)
							{
								push(dir);
								push(nx);
								push(ny);
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cca(input_map, i, j);
		}
	}


	printf("\n===================================================\n");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (input_map[i][j] == 0) printf("%3c", '.');
			else printf("%3d", input_map[i][j]);
		}
		printf("\n");
	}
	printf("===================================================\n\n");


	return 0;
}

/*

						printf("\n===================================================\n");
						for (int i = 0; i < 15; i++)
						{
							for (int j = 0; j < 15; j++)
							{
								if (input_map[i][j] == 0) printf("%3c", '.');
								else printf("%3d", input_map[i][j]);
							}
							printf("\n");
						}
						printf("===================================================\n\n");
*/