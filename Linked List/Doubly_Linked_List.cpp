#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _dnode {
	int key;
	struct _dnode* prev;
	struct _dnode* next;
}dnode;

dnode* head, *tail;

void init_dlist() {
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));

	head->prev = head;
	head->next = tail;
	tail->next = tail;
	tail->prev = head;
}

//insert a new node containing value k before node t
dnode* insert_dnode_ptr(int k, dnode* t)
{
	dnode* i;
	if (t == head) return NULL;
	
	i = (dnode*)calloc(1, sizeof(dnode));
	i->key = k;
	t->prev->next = i;
	i->prev = t->prev;
	t->prev = i;
	i->next = t;
	return i;
}

//delete the given node
int delete_dnode_ptr(dnode* p)
{
	if (p == head || p == tail) return 0;

	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);

	return 1;
}

//find the given node with a variable 'k'
dnode* find_dnode(int k)
{
	dnode* s;
	s = head->next;
	int order=0;
	while (s->key != k && s != tail)
	{
		order++;
		s = s->next;
	}
	//printf(" (key : %d ���) �� ���� : %d ��°. \n", k,order);
	return s;
}
//delete the given node with a variable 'k'
int delete_dnode(int k)
{
	dnode* s;
	s = find_dnode(k);

	if (s != tail)
	{
		s->prev->next = s->next;
		s->next->prev = s->prev;
		free(s);
		return 1;
	}
	return 0;
}

//Insert a k node before t
dnode* insert_dnode(int k, int t)
{
	dnode* s;
	dnode* i = NULL;
	s = find_dnode(t);
	if (s != tail)
	{
		i = (dnode*)calloc(1, sizeof(dnode));
		i->key = k;
		s->prev->next = i;
		i->prev = s->prev;
		s->prev = i;
		i->next = s;
	}
	return i;
}

//Ordered sorting in the linked list
dnode* ordered_insert(int k)
{
	dnode* s;
	dnode* i;
	s = head->next;
	while (s->key <= k && s != tail)s = s->next;
	i = (dnode*)calloc(1, sizeof(dnode));
	i->key = k;
	s->prev->next = i;
	i->prev = s->prev;
	s->prev = i;
	i->next = s;
	return i;
}

void delete_all()
{
	dnode* p;
	dnode* s;
	p = head->next;
	while (p != tail)
	{
		s = p;
		p = p->next;
		free(p);
	}
	head->next = tail;
	tail->prev = head;
}

void print_dlist(dnode* p)
{
	printf("\n");
	while (p != tail)
	{
		printf("%-8d", p->key);
		p = p->next;
	}
}

int main()
{
	dnode* t;
	
	init_dlist();
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5);
	ordered_insert(1);
	ordered_insert(7);
	
	print_dlist(head->next);

	t = find_dnode(5);
	printf("\nFinding 5 is %ssuccessful", t == tail ? "un" : "");

	insert_dnode(4, 5);
	print_dlist(head->next);

	insert_dnode(2, 9);
	print_dlist(head->next);

	delete_dnode(4);
	print_dlist(head->next);

	return 0;
}
