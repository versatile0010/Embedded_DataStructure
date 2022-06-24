#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://jun01.tistory.com/73
//234 tree
//1. while (current node != external node)
//  1.1 if current node is 4 node, split
//      현재 노드에 값이 4개일 때, 적절히 분할시킴
//      이때 중간값이 상위노드, 왼쪽이 작은값, 오른쪽이 큰값
//  1.2 if key < 1st value, go to 1st child
//  1.3 if key < 2nd value, go to 2nd child
//  1.4 if key < 3rd value, go to 3rd child
//  1.5 if key >= 3rd value, go to 4th child
//2. if external node is 4 node, split
//3. Merge key into external node

//값을 삭제할 때: 상위 노드에서 값을 빌려와 
//2 node (값이 1개) 를 3 node (값이 2개) 로 만든 후 값 삭제
//또는 옆의 2node와 상위노드에서 빌린 값과 함께 merge시킨 후
//4node로 만든 다음 삭제

//Red Black tree (flag로 표현)
//234 tree에서 2, 3, 4를 표현하는 것을 색깔로 대치
//(binary + 234 tree)
//left child < parent < right child

//1. the number of black nodes are same to go to the external nodes
//어떤 노드에서 시작하여 리프 노드 (external node) 까지 도달하는
//모든 경로에서 블랙 노드의 개수는 같다
//2. when node is inserted -> red
//처음 노드 삽입을 했을 때 노드는 레드이다
//3. Two consecutive reds are not allowed (rotation required)
//부모 자식간 노드는 연속해서 빨간색이 나올 수 없다
//(만약 연속으로 빨간 색이 나온다면, rotation이 필요)
//4. two children are red, then color flip is conducted (parent <-> child)
//만약 내가 블랙인데 자식이 둘다 레드면, 
//내가 레드가 되고 자식 둘 다 블랙이 됨
//5. root cannot be red
//루트 노드는 무조건 블랙이다
//(노드 삽입하여 레드가 되었다면 바로 flip 필요)
//6. red nodes do not have child or both needs to be black
//레드 노드의 자식은 양쪽 다 무조건 블랙이거나, 자식이 없다
//7. black nodes do not have child or one red / two reds / two blacks
//블랙노드의 자식은 하나의 블랙 자식을 가질 수 없다
//(레드 1개, 레드 2개, 블랙 2개는 되지만 레드1개 블랙1개나 블랙 1개만은 안됨)

//234 tree에서의 split은 RBtree에서의 color flip과 같다

//Node Insertion
//1. If current node is not external,
//	1. if two children are red, then color flip
//	2. After flipping, if needed, rotation conducted
//	3. if key < cur node, go left
//	4. if key >= cur node, go right
//2. insert a red node (if needed, rotation conducted)


//Node delelion
//red 노드만이 삭제될 수 있음
//color deflip이 일어남 (원래 flip은 내가 블랙이고 자식이 둘다 레드일 때인데,
//	이땐 자식이 둘다 블랙이고 내가 레드일 때 수행함)
//또한 deflip으로 부족할 땐 root를 red로 만든 후 rotate나 deflip 응용
typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
	int red; //1이면 레드, 0이면 블랙
}RBtree;

RBtree* head;

typedef struct wcount {
	int count;
	char word[20];
}wcount;

int wcount_cmp(const void* a, const void* b) // 단어가 서로 같은지 비교, 일반화된 버전
{
	return strcmp(((wcount*)a)->word, ((wcount*)b)->word); // 같으면 0을 리턴, 입력 매개 변수 = 포인터
}

void print_wcount(void* a) // 단어와 단어의 빈도수를 출력, 일반화된 버전
{
	printf("%s : %d\n", ((wcount*)a)->word, ((wcount*)a)->count); // 단어와 빈도 수 출력
}


void init_tree(RBtree** p) {
	*p = (RBtree*)malloc(sizeof(RBtree));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->red = 0;
}

typedef int(*FCMP)(const void*, const void*);

// 균형잡힌 나무를 형성하는데 도움을 줌
// red node 는 동시에 나타날 수 없다.
// 동시에 나타나는 경우에는 rotate 를 실행하여 조정한다.
RBtree* rotate(int key, RBtree* pivot, RBtree* base) {
	RBtree* child, * gchild;
	if (key < pivot->key || pivot == head)
		child = pivot->left;
	else
		child = pivot->right;
	if (key < child->key) { //L rotation
		gchild = child->left;
		child->left = gchild->right;
		gchild->right = child;
	}
	else { //R rotation
		gchild = child->right;
		child->right = gchild->left;
		gchild->left = child;
	}
	if (key < pivot->key || pivot == base) //부모자식간 연결 작업
		pivot->left = gchild;
	else
		pivot->right = gchild;
	return gchild;
}

//generalized version 만들면 좋다
RBtree* rbti_insert(int key, RBtree* base, int* num) {
	RBtree* t, * parent, * gparent, * ggparent;
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key) return NULL; // 이미 같은 키가 있다면 넣을 필요 없다.
		if (t->left && t->right && t->left->red && t->right->red) { // t 노드에 자식이 있는데, 둘다 red 노드이다. color flip 해야한다.
			t->red = 1;  // 내 자신은 레드 노드  // 컬러 플립
			t->left->red = t->right->red = 0; // 자식들은 모두 블랙 노드   
			if (parent->red) { // 컬러 플립을 했는데 근데 만약 나의 parent 가 red 이면 roate 한다.
				gparent->red = 1; 
				if (key < gparent->key != key < parent->key) // LR, RL 을 해야하는 경우 L, R  회전을 먼저수행
					parent = rotate(key, gparent, base);
				t = rotate(key, ggparent, base); // LL & RR rotate
				t->red = 0; 
			}
			base->left->red = 0;
		}
		//자식노드, 부모노드, 조부모노드간 관계 연결
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	t = (RBtree*)malloc(sizeof(RBtree)); //insert 할 자식노드 생성
	t->key = key;//t initialize
	t->left = NULL;
	t->right = NULL;

	if (key < parent->key || parent == base) parent->left = t;
	else parent->right = t; //크기 비교후 왼쪽 혹은 오른쪽 자식으로 배정
	(*num)++; //개수 증가

	t->red = 1; //insert된 노드는 red이다

	if (parent->red) //insert된 노드(현재 red) 의 부모 노드도 red이면 rotate 한다.
	{
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)
			parent = rotate(key, gparent, base); //rotation
		t = rotate(key, ggparent, base); //rotation
		t->red = 0; //회전 후 자식은 black
	}
	base->left->red = 0;
	return t;
}

void btv_list(RBtree* p, void(*fptr)(void*)) {
	//fptr : 함수포인터
	//나무를 입력받으면 해당 나무를 출력하는 함수
	int i;
	static int x = 0;

	if (p != NULL) {
		x += 2;
		btv_list(p->right, fptr);
		for (i = 2; i < x; i++) printf(" ");
		fptr(p);
		btv_list(p->left, fptr);
		x -= 2;
	}
}

void print_tree(void* a) {
	if (((RBtree*)a)->red) printf("%d is red \n", ((RBtree*)a)->key);
	else printf("%d is black \n", ((RBtree*)a)->key);
}



// RB 트리 위치 회전 일반화
void* gen_rotate(void* key, RBtree* pivot, RBtree* base, int* num, int width, FCMP fcmp)
{
	RBtree* child, * gchild;

	if ((fcmp(key, pivot + 1)) < 0 || pivot == base)
		child = pivot->left;
	else
		child = pivot->right;

	if (fcmp(key, child + 1) < 0) {
		gchild = child->left;
		child->left = gchild->right;
		gchild->right = child;
	}

	else {
		gchild = child->right;
		child->right = gchild->left;
		gchild->left = child;
	}

	if ((fcmp(key, pivot + 1) < 0) || pivot == base)
		pivot->left = gchild;
	else
		pivot->right = gchild;

	return gchild;
}

// RB 트리 생성 일반화
void* gen_rbti_insert(void* key, RBtree* base, int* num, int width, FCMP fcmp)
{
	RBtree* t, * parent, * gparent, * ggparent;
	ggparent = gparent = parent = base;
	t = base->left;

	while (t != NULL) {
		if (fcmp(key, t + 1) == 0) return NULL;

		if (t->left && t->right && t->left->red && t->right->red) {
			t->red = 1;
			t->left->red = t->right->red = 0;

			// 1. 색 변경했는데, 레드가 연속으로
			if (parent->red) {
				gparent->red = 1;
				if ((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
					parent = (RBtree*)gen_rotate(key, gparent, base, num, sizeof(wcount), wcount_cmp);
				t = (RBtree*)gen_rotate(key, ggparent, base, num, sizeof(wcount), wcount_cmp);
				t->red = 0;
			}
			base->left->red = 0;
		}

		// 회전 이후 연결 관계 정립
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (fcmp(key, t + 1) < 0) t = t->left;
		else t = t->right;
	}

	// 새로운 값 삽입
	t = (RBtree*)malloc(sizeof(RBtree) + width);
	memcpy(t + 1, key, width);
	t->left = NULL;
	t->right = NULL;
	if ((fcmp(key, parent + 1) < 0) || parent == base) parent->left = t;
	else parent->right = t;

	(*num)++; // 데이터 개수 하나 늘려주기
	t->red = 1; // 새롭게 삽입하는 값은 레드

	// 2. 그냥 삽입했는데 레드가 연속으로
	if (parent->red) {
		gparent->red = 1;
		if ((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
			parent = (RBtree*)gen_rotate(key, gparent, base, num, sizeof(wcount), wcount_cmp);
		t = (RBtree*)gen_rotate(key, ggparent, base, num, sizeof(wcount), wcount_cmp);
		t->red = 0;
	}

	base->left->red = 0;
	return t;
}

// RB 트리 탐색 함수, 이진 트리 탐색 함수와 동일
void* btv_search(void* key, RBtree* base, int* num, int width, FCMP fcmp)
{
	RBtree* s;
	s = base->left;

	while (s != NULL && fcmp(key, s + 1) != 0) { // 레프트와 라이트가 있는 방을 건너뛰고 그 다음 값과 비교
		if (fcmp(key, s + 1) < 0) // 찾는 값이 비교하는 값보다 작으면
			s = s->left; // 왼쪽으로 이동
		else // 찾는 값이 비교하는 값보다 크면
			s = s->right; // 오른쪽으로 이동
	}

	if (s == NULL) return NULL; // 못 찾으면 널
	else return s + 1; // 찾으면 그 값의 주소 반환
}



RBtree* find_seed(int key, RBtree* base) // find red node
{
	RBtree* del, * seed_parent, * parent;

	seed_parent = NULL;
	parent = base;
	del = base->left;

	while (del != NULL) // search red node
	{
		if (key < del->key)
		{
			if (del->red || (del->right && del->right->red))
				seed_parent = parent; /* 빨강 노드나 오른쪽 자식이 빨간 노드 찾기 */
			parent = del;
			del = del->left;
		}
		else
		{
			if (del->red || (del->left && del->left->red))
				seed_parent = parent; /* 빨강 노드나 왼쪽 자식이 빨간 노드 찾기 */
			parent = del;
			del = del->right;
		}
	}

	return seed_parent;
}

void make_leaf_red(int key, RBtree* base)
{
	RBtree* seed_parent, * seed, * seed_child;

	seed_parent = find_seed(key, base); /* 빨강 씨앗을 찾음 */

	if (seed_parent == NULL) /* 빨강 씨앗이 없으면 */
	{
		seed_parent = base;
		seed = seed_parent->left;
		seed->red = 1; /* 뿌리노드를 빨강으로 하고 씨앗으로 삼는다 */
	}
	else
	{
		if (key < seed_parent->key || seed_parent == base)
			seed = seed_parent->left;
		else
			seed = seed_parent->right;
	}

	if (!seed->red) /* 씨앗이 빨강이 아니면 그 자식이 빨강이다 */
	{/* 그래서 회전을 하여 빨강을 끌어 올린다 */
		if (key < seed->key)
			seed_child = seed->right;
		else
			seed_child = seed->left;

		seed->red = 1;
		seed_child->red = 0;
		seed_parent = rotate(seed_child->key, seed_parent, base); /* 회전 */
	}

	while (seed->left && seed->right)
	{/* 외부 노드가 아닐 동안 */
		seed->red = 0; /* 역색상 변환 */
		seed->right->red = seed->left->red = 1;
		if (key < seed->key)
		{
			if ((seed->right->left || seed->right->right) && (seed->right->left->red || seed->right->right->red))
			{   /* 회전이 필요하면 회전을 한다 */
				if (seed->right->left && seed->right->left->red)
				{/* RL회전이 필요 */
					seed->right->red = 0;
					rotate(seed->right->left->key, seed, base);
				}
				else
					seed->right->right->red = 0;

				rotate(seed->right->key, seed_parent, base);
			}
			seed_parent = seed;
			seed = seed->left;
		}
		else
		{
			if ((seed->left->left || seed->left->right) && (seed->left->left->red || seed->left->right->red))
			{/* 회전이 필요하면 회전을 한다 */
				if (seed->left->right && seed->left->right->red)
				{/* LR회전이 필요 */
					seed->left->red = 0;
					rotate(seed->left->right->key, seed, base);
				}
				else
					seed->left->left->red = 0;

				rotate(seed->left->key, seed_parent, base);
			}
			seed_parent = seed;
			seed = seed->right;
		}
	}
}

RBtree* rbti_delete(int key, RBtree* base, size_t* num)
{
	RBtree* parent, * del, * center, * pcenter, * son;
	int temp;
	parent = base;
	del = base->left;

	while (key != del->key && del != NULL)
	{
		/* 삭제할 키를 찾음 */
		parent = del;
		if (key < del->key)
			del = del->left;
		else
			del = del->right;
	}
	if (del == NULL)
		return NULL; /* 삭제할 키를 찾지 못함 */

	if (del->right && del->left)
	{

		/* 자식이 두 개이면, 즉 내부 노드이면 */
		pcenter = del; /* 삭제할 노드를 대체할 노드를 찾음 */
		center = del->right;

		while (center->left != NULL)
		{
			pcenter = center;
			center = center->left; /* center는 대체할 키임 */
		}

		del->key = center->key; /* 삭제할 키를 대체할 키로 바꿈 */
		del = center; /* 이제 center를 삭제하도록 조정 */
		parent = pcenter;
		key = del->key;
	}

	if (del->left || del->right)
	{

		/* 자식이 하나인 경우, 자식이 하나면 반드시 빨강 자식이다 */
		if (del->left)
			son = del->left;
		else
			son = del->right;

		son->red = 0;
	}
	else if (del->left == NULL && del->right == NULL)
	{

		/* 자식이 없는 경우, 빨강이면 그냥 삭제, 검정이면 2-노드이므로 3-노드나 4-노드로 변환 후에 삭제*/
		if (!del->red)
			make_leaf_red(del->key, base);

		son = NULL;
	}

	base->left->red = 0;

	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;

	free(del);

	(*num)--;

	return parent;
}



void main() {
	int num = 0;
	init_tree(&head);
	rbti_insert(1, head, &num);
	rbti_insert(3, head, &num);
	rbti_insert(5, head, &num);
	rbti_insert(7, head, &num);
	rbti_insert(9, head, &num);
	btv_list(head->left, print_tree);
}

