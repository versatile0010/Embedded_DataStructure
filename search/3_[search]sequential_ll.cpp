#include "ds.h"

/*
	memcpy(t+1, key, width)
	-> t ���� next �����Ͱ� �������.
	-> t+1*(sizeof(node)) �� ���־�� key ���� access ����
*/

void init_list(node** p) {
	// p = &t
	*p = (node*)malloc(sizeof(node));
	(*p)->next = NULL;
}

void* llv_search(void* key, node* base, int* num, int width, FCMP fcmp, int* index) {
	node* t;
	int i = 0;
	t = base->next; 
	while (fcmp(t + 1, key) != 0 && t != NULL)
	{
		t = t->next;
		i++;
	}
	if(t != NULL)
		*index = i;
	//printf("t+1 = %d\n", *(int*)(t + 1));
	return (t = NULL ? NULL : t + 1);
}

void* llv_insert(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t;
	t = (node*)malloc(sizeof(node) + width);
	memcpy(t + 1, key, width); //t ������ ĭ
	t->next = base->next; //base ���� �ִ� ��带 t ������ �ű�
	base->next = t; //base ���� t�� ����
	(*num)++;
	return t;
}

void* llv_delete(void* key, node* base, int* num, int width, FCMP fcmp, int* index)
{
	node* t, * s;
	s = base;
	t = base->next;
	int count = 0;
	while (t != NULL && fcmp(t + 1, key) != 0) {
		s = t;
		t = t->next;
		count++;
	}//search first
	if (index != NULL) {
		if (t == NULL) {
			*index = -1;
			return NULL;
		}
		else
			*index = count;
	}
	if (t == NULL) return NULL;
	s->next = t->next;
	free(t);
	return s;
}