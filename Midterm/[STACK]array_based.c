#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int stack[MAX];
int top;

void init_stack()
{
	top = -1;
}
int push(int t)
{
	if (top >= MAX - 1)
	{
		printf("Stack Overflow!!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}
int pop()
{
	if (top < 0)
	{
		printf("Stack Underflow!!\n");
		return -1;
	}
	return stack[top--];
}
int isitempty()
{
	return (top < 0) ? 1 : 0;
}
