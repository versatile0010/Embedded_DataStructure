#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
Simply Linked list
*/

typedef struct _node {
	int key;
	struct _node* next;
}node;

node* head, * tail;

void init_list()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

// Insert a new node after the current one(k)
node* insert_after(int k, node* t)
{
	node* temp;
	temp = (node*)calloc(1, sizeof(node));
	temp->key = k;
	temp->next = t->next;
	t->next = temp;

	return temp;
}

//Delete the next node
int delete_next(node* t)
{
	node* temp;
	if (t->next = tail)
	{
		return 0;
	}
	temp = t->next;
	t->next = t->next->next;
	free(temp);
	return 1;
}

node* find_node(int k)
{
	node* temp;
	temp = head->next;
	while (temp->key != k && temp != tail)
	{
		temp = temp->next;
	}
	return temp;
}

//Delete the node containing a given key value
int delete_node(int k)
{
	node* s, * p;
	p = head;
	s = head->next;
	while (s->key != k && s != tail)
	{
		p = p->next;
		s = s->next;
	}
	if (s != tail)
	{
		p->next = s->next;
		free(s);
		return 1;
	}
	else return 0;
}

//Insert the node containing a given value
//Insert t before k
node* insert_node(int t, int k)
{
	node* s, * p, * r;
	p = head;
	s = head->next;
	while (s->key != k && s != tail)
	{
		p = p->next;
		s = s->next;
	}
	if (s != tail)
	{
		r = (node*)calloc(1, sizeof(node));
		r->key = t;
		p->next = r;
		r->next = s;
	}
	return p->next;
}

node* ordered_insert(int k)
{
	node* s, * p, * r;
	p = head;
	s = head->next;
	while (s->key <= k && s != tail)
	{
		p = p->next;
		s = s->next;
	}
	r = (node*)calloc(1, sizeof(node));
	r->key = k;
	p->next = r;
	r->next = s;
	return r;
}
node* delete_all()
{
	node* s, * t;
	t = head->next;
	while (t != tail)
	{
		s = t;
		t = t->next;
		free(s);
	}
	head->next = tail;
	tail->next = head;
}
void print_list(node* t)
{
	while (t != tail)
	{
		printf("%-8d", t->key);
		t = t->next;
	}
}
