#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node* next;
}node;

node* head, * tail;

void init_stack()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

int push(int k) {
	node* t;
	if ((t = (node*)malloc(sizeof(node))) == NULL) {
		printf("Out of Memory !!\n");
		return -1;
	}
	t->key = k;
	t->next = head->next;
	head->next = t;
} //새로운 노드는 무조건 head의 뒤에 삽입됨

int pop() {
	node* t;
	int k;
	if (head->next == tail) {
		printf("Stack Underflow!!\n");
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
	node* t, *s;
	t = head->next;
	while (t != tail)
	{
		s = t;
		t = t->next;
		free(s);
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

int get_stack_top()
{
	return (head->next == tail) ? -1 : head->next->key;
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
int is_stack_empty() {
	if (head->next == tail) return 1;
	else return 0;
}
void advanced_postfix_list(char* dst, char* src)
{
	char c;
	init_stack();
	while (*src)
	{
		if (*src == '(')
		{
			push(*src);
			src++;
		}
		else if (*src == ')')
		{
			while (get_stack_top() != '(')
			{
				*dst++ = pop();
				*dst++ = ' ';
			}
			pop();
			src++;
		}
		else if (is_op(*src))
		{
			while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src))
			{
				*dst++ = pop();
				*dst++ = ' ';
			}
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9')
		{
			do
			{
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else src++;
	}

	while (!is_stack_empty()){
		*dst++ = pop();
		*dst++ = ' ';
	}
	*dst = 0;
}

void main() {
	char exp[256];
	char src[256] = "(1*(2+3/4)+5)/6+7";

	advanced_postfix_list(exp, src);
	printf("Postfix representation : %s\n", exp);
}