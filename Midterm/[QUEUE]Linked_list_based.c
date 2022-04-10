/*
stack : �� ���߿� ���� �����͸� ���� �� �� ���� (LIFO)
Queue : �� ���� ���� �����ͺ��� ���������� �� �� ���� (FIFO)

put : Queue�� �� �ڿ� �����͸� �ִ´� (rear
get : Queue�� �� ���� �����͸� ���� (front)

Queue�� �� �� ���¿��� �����͸� ���� front���� ��� �ٲ�� ������
front�� rear�� circular�� queue�� ���� ���� ���� �ְ� ���� �ݺ��Ѵ�
*/

//Linked list, doubly ���

#include <stdio.h>
#include <stdlib.h>

typedef struct _dnode {
	int key;
	struct _dnode* prev;
	struct _dnode* next;
}dnode;

dnode* head, * tail;

void init_queue() {
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));
	head->prev = head;
	head->next = tail;
	tail->prev = head;
	tail->next = tail;
}


int put(int k) {
	dnode* t;
	if ((t = (dnode*)malloc(sizeof(dnode))) == NULL) {
		printf("Out of Memory !!\n");
		return -1;
	}
	t->key = k;
	tail->prev->next = t;
	t->prev = tail->prev;
	tail->prev = t;
	t->next = tail;
	return k;
} //���ο� ���� tail�� ��

int get() {
	dnode* t;
	int k;

	t = head->next; // head �ڿ� �ִ� ��带 t�� ����

	if (t == tail) {
		printf("Stack Underflow!!\n");
		return -1;
	}
	k = t->key; //head �ڿ� �ִ� ����� Ű���� �޾ƿ���
	head->next = t->next; //head�� �ڿ� (t �ڿ� �ִ�) ��带 ����
	//t �ڿ� �ִ� ���� ���� head�� ��ĭ �ڿ� �־���
	t->next->prev = head; //(t�� �ڿ� �ִ�) ����� �տ� head�� ����

	free(t); //�޸� ����
	return k;
} //head�� �ڿ� �ִ� ������ ����

//linked list ����� ũ�� �����̳� �޸� ���𿡼� ������

void clear_queue() { //Delete all 
	dnode* t, * s;
	t = head->next; //head �� ���� t�� ����

	while (t != tail) { //t�� tail�� �Ǿ� ����Ʈ�� �� ������
		s = t; //head �� ��� t�� s�� ����
		t = t->next; //t�� t �� ��带 ����
		free(s); //��� �ϳ��� ����
	}
	head->next = tail;
	tail->prev = head;
	//�������� head�� tail�� ���� ��������
}

void print_queue() {
	dnode* t;
	t = head->next;
	while (t != tail) {
		printf("%-6d", t->key);
		t = t->next; //��带 ��ĭ�� �ڷ� �̵��ϸ鼭 ����ϴ°�
	} //stack�� ����
}

void main() {
	int k;
	init_queue();

	put(3);
	put(6);
	put(9);
	put(1);
	put(6);
	put(3);

	print_queue();
	printf("queue finish \n");

	get();

	print_queue();
	printf("queue finish \n");

	put(4);
	put(8);
	put(7);
	put(2);
	put(0);
	put(1);
	print_queue();
	//overflow �߻����� ����

	init_queue();
	get(); //stack underflow
}