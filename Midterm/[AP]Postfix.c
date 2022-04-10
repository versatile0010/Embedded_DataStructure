#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct _node {
	int key;
	struct _node* next;
}node;

node* head, * tail;
int stack[MAX];
int top = -1;

void init_stack()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}
int push(int k) {
	node* t;
	if ((t = (node*)malloc(sizeof(node))) == NULL)
	{
		printf("Out of Memory\n");
		return -1;
	}
	t->key = k;
	t->next = head->next;
	head->next = t;

	return k;
}
int pop()
{
	node* t;
	int k;
	if (head->next == tail)
	{
		printf("Stack underflow!!\n");
		return -1;
	}
	t = head->next;
	k = t->key;
	head->next = t->next;
	free(t);
	return k;
}
void clear()
{
	node* t, * s;
	t = head->next;
	while (t != tail)
	{
		s = t;
		t = t->next;
		free(t);
	}
	head->next = tail;
}
void print_stack()
{
	node* t;
	t = head->next;
	while (t != tail)
	{
		printf("%-6d", t->key);
		t = t->next;
	}
}
double calcPostFixEq(char* p)
{
	char j;
	init_stack();
	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			j = atoi(p);
			push(j);
			p++;
		}
		else if (*p == '+')
		{
			push(pop() + pop());
			p++;
		}
		else if (*p == '-')
		{
			j = pop();
			push(pop() - j);
			p++;
		}
		else if (*p == '*')
		{
			push(pop() * pop());
			p++;
		}
		else if (*p == '/')
		{
			j = pop();
			push(pop() / j);
			p++;
		}
		else
			p++;
	}
	return pop();
}

//input : string of equation
//output : postfix representaion
void postfix(char* dst, char* src) 
{
	char c;
	init_stack();
	while (*src)
	{
		if (*src == ')')
		{ //src 주소가 가리키는 string 문자를 순회
			*dst++ = pop(); 
			*dst++ = ' ';
			src++;
		}
		else if (*src == '+' || *src == '-' ||
			*src == '*' || *src == '/')
		{
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9')
		{
			do {
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else
			src++;
	}
	*dst = 0;
}


void main()
{
	char eqn[100] = "8 2 / 2 2 + *";
	int result;
	result = calcPostFixEq(eqn);
	printf("\nresult = % d\n", result);

	char exp[256];
	char src[256] = "(1+(2*3))";

	postfix(exp, src);
	printf("Postfix representation : %s\n", exp);

}
