#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node* next;
}node;

node* head; node* tail;

void init_list()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

node* insert_after(int k, node* t)
{
	node* temp;
	temp = (node*)calloc(1, sizeof(node));
	temp->key = k;
	temp->next = t->next;
	t->next = temp;

	return temp;
}

int delete_next(node* t)
{
	node* temp;
	if (t->next == tail) return 0;
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
		temp = temp->next;
	return temp;
}// ★ 찾고자 하는 key 를 가진 node 의 order 을 반환할 수 있나요? -> 시험

int get_order_find_node(int k)
{
	node* temp; int order=0;
	temp = head->next;
	while (temp->key != k && temp != tail)
	{
		order++;
		temp = temp->next;
	}
	return order;
}

int delete_node(int k)
{
	node* s, * p; // p is previous node of s
	p = head;
	s = p->next;
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

node* insert_node(int t, int k) //insert t before k
{
	node* s, * p, * r;
	p = head;
	s = p->next;
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
	s = p->next;
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
	return head;
}

void print_list(node* t)
{
	while (t != tail)
	{
		printf("%-8d", t->key);
		t = t->next;
	}
}

int main()
{
	node* t;
	init_list();
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5);
	ordered_insert(1);
	ordered_insert(7);

	printf("Print out initial list\n");
	print_list(head->next);
	printf("\n");

	printf("\n%d's order : %d\n",5, get_order_find_node(5));

	printf("Find the node containing 5, and insert 6 after 5 \n");
	t = find_node(5);
	insert_after(6, t);
	print_list(head->next);
	printf("\n");

	printf("Delete node 5\n");
	delete_node(5);
	print_list(head->next);
	printf("\n");

	printf("Delete all the node\n");
	delete_all();
	print_list(head->next);
	printf("\n");




	return 0;
}
