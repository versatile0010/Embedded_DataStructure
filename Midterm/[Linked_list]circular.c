#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node* next;
}node;

node* head;

void insert_node(int k)
{
	node* t;
	int i;
	t = (node*)calloc(1, sizeof(node));
	t->key = 1;
	head = t;
	for (i = 2; i <= k; i++)
	{
		t->next = (node*)calloc(1, sizeof(node));
		t = t->next;
		t->key = i;
	}
}
void delete_after(node* t)
{
	node* s;
	s = t->next;
	t->next = t->next->next;
	free(s);
}
void josephus(int n, int m)
{
	node* t;
	int i;
	insert_nodes(n);
	t = head;
	printf("\nAnser :");
	while (t != t->next)
	{
		for (i = 0; i < m - 1; i ++)
			t = t->next;
		printf("%d ", t->next->key);
		delete_after(t);
	}
	printf("%d ", t->next->key);
}
