#include <stdio.h>
#include <stdlib.h>

#define MAX 100
// https://yoongrammer.tistory.com/70

typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
}RBtree;

RBtree* head, * tail;
RBtree* stack[MAX]; //stack이 array of pointer
RBtree* queue[MAX]; //queue가 array of pointer
//stack, queue에 들어가야 하는 것이 주소이므로
int top, front, rear;

void init_stack() {
	top = -1;
} //preorder, postorder, inorder

void init_queue() {
	front = rear = 0;
} //levelorder

int is_stack_empty() {
	return(top == -1);
} //stack underflow 방지

int is_queue_empty() {
	return(front == rear);
} //queue underflow 방지

RBtree* push(RBtree* t) {
	stack[++top] = t;
	return t;
}

RBtree* pop() {
	return stack[top--];
}

RBtree* put(RBtree* t) {
	queue[rear] = t;
	rear = ++rear % MAX;
	return t;
}

RBtree* get() {
	RBtree* t;
	t = queue[front];
	front = ++front % MAX;
	return t;
}

void init_tree() {
	head = (RBtree*)calloc(1, sizeof(RBtree));
	tail = (RBtree*)calloc(1, sizeof(RBtree));

	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
} //Tree 초기화 (head -> tail)

int is_operator(int k) {
	return (k == '+' || k == '-' || k == '*' || k == '/');
} //연산자 여부 체크

void visit(RBtree* t) {
	printf("%c", t->key);
} //Tree traverse마다 해당 key값 출력

void preorder_traverse(RBtree* t) {
	if (t != tail) {
		visit(t);
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}
}

void postorder_traverse(RBtree* t) {
	if (t != tail) {
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}

void inorder_traverse(RBtree* t) {
	if (t != tail) {
		inorder_traverse(t->left);
		visit(t);
		inorder_traverse(t->right);
	}
}

void levelorder_traverse(RBtree* t) {
	put(t);

	while (!is_queue_empty()) {
		t = get();
		visit(t);

		if (t->left != tail)
			put(t->left);
		if (t->right != tail)
			put(t->right);
	}
}

//1. when you meet operands, make a node and push it to the stack (피연산자)
//2. when you meet the operators, (연산자)
// 2.1 pop and make a right child
// 2.2 pop and make a left child
// 2.3 after that, push the operator
//3. last node in the stack becomes root
//postfix

RBtree* make_parse_tree(char* p) {
	RBtree* t;
	while (*p) {
		while (*p == ' ') //해당 문자열이 공백이면
			p++; //문자열 한 칸 이동
		t = (RBtree*)calloc(1, sizeof(RBtree)); //노드 메모리 allocate
		t->key = *p;
		t->left = tail;
		t->right = tail;
		if (is_operator(*p)) { //p가 연산자라면
			t->right = pop(); //자식노드들을 모두 pop
			t->left = pop();
		}
		push(t); //자기자신을 push
		p++; //문자열 한 칸 이동
	}
	return pop();
}

void main() {
	char post[256]; //equation 입력받기 위한 배열
	init_stack();
	init_queue();
	init_tree(); //Stack, queue, tree 초기화

	while (1) {
		printf("\n\nInput postfix expression : ");
		//ABC*D-+
		gets_s(post);

		if (*post == NULL) break;
		head->right = make_parse_tree(post);

		printf("\nPreorder traverse : ");
		preorder_traverse(head->right);
		printf("\nPostorder traverse : ");
		postorder_traverse(head->right);
		printf("\nInorder traverse : ");
		inorder_traverse(head->right);
		printf("\nLevelorder traverse : ");
		levelorder_traverse(head->right);
	}
}