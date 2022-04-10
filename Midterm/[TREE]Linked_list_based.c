#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
}node;

node* head, * tail;
node* stack[MAX];
node* queue[MAX];
int top, front, rear;

void init_stack() {
	top = -1;
}
void init_queue() {
	front = rear = 0;
}
int is_stack_empty() {
	return (top == -1);
}
int is_queue_empty() {
	return (front == rear);
}
node* push(node* t) {
	stack[++top] = t;
	return t;
}
node* pop() {
	return stack[top--];
}
node* put(node* t) {
	queue[rear] = t;
	rear = ++rear % MAX;
	return t;
}
node* get() {
	node* t;
	t = queue[front];
	front = ++front % MAX;
	return t;
}

void visit(node * t)
{
	printf("%c visited\n", t->key);
}
void init_tree()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));

	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}

void preorder_traverse(node* t)
{
	/*
	1. Visit the root
	2. Visit the left subtree
	3. Visit the right subtree
	*/
	if (t != tail)
	{
		visit(t);
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}
}

void inorder_traverse(node* t)
{
	if (t != tail)
	{
		/*
		1. Visit the left subtree
		2. Visit the root
		3. Visit the right subtree
		*/
		inorder_traverse(t->left);
		visit(t);
		inorder_traverse(t->right);
	}
}

void postorder_traverse(node* t)
{
	if (t != tail)
	{
		/*
		1. Visit the left subtree
		2. Visit the right subtree
		3. Visit the root
		*/
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}

void levelorder_traverse(node* t)
{
	/*
	1. Put the root in the queue
	2. If the queue is not empty,
		2.1. t=get() and visit ¡°t¡±
		2.2. If t has a left child, then put it
		2.3. If t has a right child, then put it
	3. Finish (queue is empty)
	*/

	put(t);
	while (!is_queue_empty())
	{
		t = get();
		visit(t);

		if (t->left != tail)
			put(t->left);
		if (t->right != tail)
			put(t->right);
	}
}

int is_op(int k)
{
	return(k == '+' || k == '-'
		|| k == '*' || k == '/');
}
int precedence(int op)
{
	if (op == '(') return 0;
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	else return 3;
}

node* make_parse_tree(char* p)
{
	node* t;
	while (*p)
	{
		while (*p == ' ')p++;
		t = (node*)calloc(1, sizeof(node));
		t->key = *p;
		t->left = tail;
		t->right = tail;
		if (is_op(*p))
		{
			t->right = pop();
			t->left = pop();
		}
		push(t);
		p++;
	}
	return pop();
}

void main()
{
	char post[256];
	init_stack();
	init_queue();
	init_tree();

	while (1) {
		printf("\n\nInput postfix expression : ");
		gets(post);

		if (*post == NULL) break;
		head->right = make_parse_tree(post);

		printf("\nPreorder traverse : \n");
		preorder_traverse(head->right);
		printf("\nPostorder traverse : \n");
		postorder_traverse(head->right);
		printf("\nInorder traverse : \n");
		inorder_traverse(head->right);
		printf("\nLevelorder traverse : \n");
		levelorder_traverse(head->right);
	}
}