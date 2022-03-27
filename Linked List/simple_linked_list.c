#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key; //store a value
	struct _node* next; // indicating the next position
}node;

node* head;
node* tail;

void init_list()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

//insert a new node after the current node t
node* insert_after(int k, node* t)
{
	node* temp;
	temp = (node*)calloc(1, sizeof(node)); //create new node
	temp->key = k;
	temp->next = t->next;
	t->next = temp;

	return temp;
}

int delete_next(node* t) // delete next node of t
{
	node* temp;
	if (t->next == tail) return 0; // check the type of the current node
	temp = t->next;
	t->next = t->next->next;
	free(temp);
	return 1;
}

// find the node containing a given key value
node* find_node(int k)
{
	node* temp;
	temp = head->next;
	while (temp->key != k && temp != tail)
		temp = temp->next;
	return temp;
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

//insert the node containing a given key value.
node* insert_node(int t, int k) // insert t before k
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
		r = (node*)calloc(1, sizeof(node)); // create new node
		r->key = t; 
		p->next = r;
		r->next = s;
	}
	return p->next;
}

//Ordered sorting in the linked list(dynamic linking)
node* ordered_insert(int k)
{
	node* s, * p, * r;
	p = head;
	s = p->next;
	while (s->key <= k && s != tail) {
		p = p->next;
		s = p->next;
	}
	r = (node*)calloc(1, sizeof(node));
	r->key = k;
	p->next = r;
	r->next = s;
	return r;
}

node* delete_all()
{
	node* s;
	node* t;
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

void main() {
	node* t;
	init_list();
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5);
	ordered_insert(1);
	ordered_insert(7);

	print_list(head->next); //print out initial list
	printf("\n");

	t = find_node(5); // Find the node containing '5'

	insert_after(6, t); // insert 6 after 5

	print_list(head->next); //print out
	printf("\n");

	delete_node(5); // delete node 5

	print_list(head->next); // print out

	printf("\n");
	delete_all();
}
