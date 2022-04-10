#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 10

int front;
int rear;
int queue[QUEUE_MAX];

void init_queue()
{
	front = 0;
	rear = 0;
}
void clear_queue()
{
	front = rear;
}
int put(int k)
{
	if ((rear + 1) % QUEUE_MAX == front)
	{
		printf("Queue overflow!!\n");
		return -1;
	}
	queue[rear] = k;
	rear = ++rear % QUEUE_MAX;
	return k;
}
int get()
{
	int j;
	if (front == rear)
	{
		printf("Queue underflow!!!\n");
		return -1;
	}
	j = queue[front];
	front = ++front % QUEUE_MAX;

	return j;
}

void print_queue() {
	int k;
	for (k = front; k != rear; k = ++k % QUEUE_MAX) {
		printf("%-6d", queue[k]);
	} //front부터 시작하여 rear까지 print
	//k % MAX가 반복적으로 나타나는 이유는 Circular 형태이기 때문
	printf("\n");
}

void main()
{
	int k;
	init_queue();
	put(3);
	put(6);
	put(9);
	put(1);
	put(6);
	put(3);

	printf("%d\n", get());
	put(4);
	put(8);
	put(7);
	put(2);
	put(0);

	clear_queue();
	get();
}