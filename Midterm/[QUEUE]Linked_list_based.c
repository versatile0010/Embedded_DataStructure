/*
stack : 맨 나중에 넣은 데이터를 먼저 뺄 수 있음 (LIFO)
Queue : 맨 먼저 넣은 데이터부터 순차적으로 뺄 수 있음 (FIFO)

put : Queue의 맨 뒤에 데이터를 넣는다 (rear
get : Queue의 맨 앞의 데이터를 뺀다 (front)

Queue가 꽉 찬 상태에서 데이터를 빼면 front값이 계속 바뀌기 때문에
front와 rear가 circular한 queue를 빙빙 돌며 값을 넣고 빼고 반복한다
*/

//Linked list, doubly 기반

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
} //새로운 노드는 tail의 앞

int get() {
	dnode* t;
	int k;

	t = head->next; // head 뒤에 있던 노드를 t로 지정

	if (t == tail) {
		printf("Stack Underflow!!\n");
		return -1;
	}
	k = t->key; //head 뒤에 있던 노드의 키값을 받아오고
	head->next = t->next; //head의 뒤에 (t 뒤에 있던) 노드를 연결
	//t 뒤에 있던 노드는 원래 head의 두칸 뒤에 있었음
	t->next->prev = head; //(t의 뒤에 있던) 노드의 앞에 head를 연결

	free(t); //메모리 해제
	return k;
} //head의 뒤에 있는 노드부터 나옴

//linked list 방식은 크기 제한이나 메모리 선언에서 유동적

void clear_queue() { //Delete all 
	dnode* t, * s;
	t = head->next; //head 뒤 노드로 t를 지정

	while (t != tail) { //t가 tail이 되어 리스트가 빌 때까지
		s = t; //head 뒤 노드 t를 s로 지정
		t = t->next; //t는 t 뒤 노드를 지정
		free(s); //노드 하나씩 삭제
	}
	head->next = tail;
	tail->prev = head;
	//마지막에 head와 tail을 서로 연결해줌
}

void print_queue() {
	dnode* t;
	t = head->next;
	while (t != tail) {
		printf("%-6d", t->key);
		t = t->next; //노드를 한칸씩 뒤로 이동하면서 출력하는것
	} //stack과 같다
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
	//overflow 발생하지 않음

	init_queue();
	get(); //stack underflow
}