#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key; //store a value
	struct _node* next; // indicating the next position
}node;

node* head;


void init_list()
{
	head = (node*)calloc(1, sizeof(node));
	head->next = head;
}
//insert a new node after the current node t

//Joshep's problem
void insert_nodes(int k)
{
	node* t;
	int i;
	t = (node*)calloc(1, sizeof(node));
	t->key = 1;
	head = t;
	for (i = 2; i <= k; i++)
	{
		t->next = (node*)malloc(sizeof(node));
		t = t->next;
		t->key = i;
	}
	t->next = head;
}

void delete_after(node* t)
{
	node* s;
	s = t->next;
	t->next = t->next->next;
	free(s);
}
void josephus(int n, int m) // n : last value, m : interval
{
	node* t;
	int i;

	insert_nodes(n); //make a circular linked list
	t = head;
	printf("\nAnswer :");
	while (t != t->next)
	{
		for (i = 0; i < m-1; i++) t = t->next;
		printf("%d", t->next->key);
		delete_after(t);
	}
	printf("%d", t->key);
}

int main() {
	int n, m;
	printf("Enter N and M :");
	scanf("%d %d", &n, &m);

	josephus(n, m);
}