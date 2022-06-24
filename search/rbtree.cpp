#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://jun01.tistory.com/73
//234 tree
//1. while (current node != external node)
//  1.1 if current node is 4 node, split
//      ���� ��忡 ���� 4���� ��, ������ ���ҽ�Ŵ
//      �̶� �߰����� �������, ������ ������, �������� ū��
//  1.2 if key < 1st value, go to 1st child
//  1.3 if key < 2nd value, go to 2nd child
//  1.4 if key < 3rd value, go to 3rd child
//  1.5 if key >= 3rd value, go to 4th child
//2. if external node is 4 node, split
//3. Merge key into external node

//���� ������ ��: ���� ��忡�� ���� ������ 
//2 node (���� 1��) �� 3 node (���� 2��) �� ���� �� �� ����
//�Ǵ� ���� 2node�� ������忡�� ���� ���� �Բ� merge��Ų ��
//4node�� ���� ���� ����

//Red Black tree (flag�� ǥ��)
//234 tree���� 2, 3, 4�� ǥ���ϴ� ���� ����� ��ġ
//(binary + 234 tree)
//left child < parent < right child

//1. the number of black nodes are same to go to the external nodes
//� ��忡�� �����Ͽ� ���� ��� (external node) ���� �����ϴ�
//��� ��ο��� �� ����� ������ ����
//2. when node is inserted -> red
//ó�� ��� ������ ���� �� ���� �����̴�
//3. Two consecutive reds are not allowed (rotation required)
//�θ� �ڽİ� ���� �����ؼ� �������� ���� �� ����
//(���� �������� ���� ���� ���´ٸ�, rotation�� �ʿ�)
//4. two children are red, then color flip is conducted (parent <-> child)
//���� ���� ���ε� �ڽ��� �Ѵ� �����, 
//���� ���尡 �ǰ� �ڽ� �� �� ���� ��
//5. root cannot be red
//��Ʈ ���� ������ ���̴�
//(��� �����Ͽ� ���尡 �Ǿ��ٸ� �ٷ� flip �ʿ�)
//6. red nodes do not have child or both needs to be black
//���� ����� �ڽ��� ���� �� ������ ���̰ų�, �ڽ��� ����
//7. black nodes do not have child or one red / two reds / two blacks
//������� �ڽ��� �ϳ��� �� �ڽ��� ���� �� ����
//(���� 1��, ���� 2��, �� 2���� ������ ����1�� ��1���� �� 1������ �ȵ�)

//234 tree������ split�� RBtree������ color flip�� ����

//Node Insertion
//1. If current node is not external,
//	1. if two children are red, then color flip
//	2. After flipping, if needed, rotation conducted
//	3. if key < cur node, go left
//	4. if key >= cur node, go right
//2. insert a red node (if needed, rotation conducted)


//Node delelion
//red ��常�� ������ �� ����
//color deflip�� �Ͼ (���� flip�� ���� ���̰� �ڽ��� �Ѵ� ������ ���ε�,
//	�̶� �ڽ��� �Ѵ� ���̰� ���� ������ �� ������)
//���� deflip���� ������ �� root�� red�� ���� �� rotate�� deflip ����
typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
	int red; //1�̸� ����, 0�̸� ��
}RBtree;

RBtree* head;

typedef struct wcount {
	int count;
	char word[20];
}wcount;

int wcount_cmp(const void* a, const void* b) // �ܾ ���� ������ ��, �Ϲ�ȭ�� ����
{
	return strcmp(((wcount*)a)->word, ((wcount*)b)->word); // ������ 0�� ����, �Է� �Ű� ���� = ������
}

void print_wcount(void* a) // �ܾ�� �ܾ��� �󵵼��� ���, �Ϲ�ȭ�� ����
{
	printf("%s : %d\n", ((wcount*)a)->word, ((wcount*)a)->count); // �ܾ�� �� �� ���
}


void init_tree(RBtree** p) {
	*p = (RBtree*)malloc(sizeof(RBtree));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->red = 0;
}

typedef int(*FCMP)(const void*, const void*);

// �������� ������ �����ϴµ� ������ ��
// red node �� ���ÿ� ��Ÿ�� �� ����.
// ���ÿ� ��Ÿ���� ��쿡�� rotate �� �����Ͽ� �����Ѵ�.
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
	if (key < pivot->key || pivot == base) //�θ��ڽİ� ���� �۾�
		pivot->left = gchild;
	else
		pivot->right = gchild;
	return gchild;
}

//generalized version ����� ����
RBtree* rbti_insert(int key, RBtree* base, int* num) {
	RBtree* t, * parent, * gparent, * ggparent;
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key) return NULL; // �̹� ���� Ű�� �ִٸ� ���� �ʿ� ����.
		if (t->left && t->right && t->left->red && t->right->red) { // t ��忡 �ڽ��� �ִµ�, �Ѵ� red ����̴�. color flip �ؾ��Ѵ�.
			t->red = 1;  // �� �ڽ��� ���� ���  // �÷� �ø�
			t->left->red = t->right->red = 0; // �ڽĵ��� ��� �� ���   
			if (parent->red) { // �÷� �ø��� �ߴµ� �ٵ� ���� ���� parent �� red �̸� roate �Ѵ�.
				gparent->red = 1; 
				if (key < gparent->key != key < parent->key) // LR, RL �� �ؾ��ϴ� ��� L, R  ȸ���� ��������
					parent = rotate(key, gparent, base);
				t = rotate(key, ggparent, base); // LL & RR rotate
				t->red = 0; 
			}
			base->left->red = 0;
		}
		//�ڽĳ��, �θ���, ���θ��尣 ���� ����
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	t = (RBtree*)malloc(sizeof(RBtree)); //insert �� �ڽĳ�� ����
	t->key = key;//t initialize
	t->left = NULL;
	t->right = NULL;

	if (key < parent->key || parent == base) parent->left = t;
	else parent->right = t; //ũ�� ���� ���� Ȥ�� ������ �ڽ����� ����
	(*num)++; //���� ����

	t->red = 1; //insert�� ���� red�̴�

	if (parent->red) //insert�� ���(���� red) �� �θ� ��嵵 red�̸� rotate �Ѵ�.
	{
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)
			parent = rotate(key, gparent, base); //rotation
		t = rotate(key, ggparent, base); //rotation
		t->red = 0; //ȸ�� �� �ڽ��� black
	}
	base->left->red = 0;
	return t;
}

void btv_list(RBtree* p, void(*fptr)(void*)) {
	//fptr : �Լ�������
	//������ �Է¹����� �ش� ������ ����ϴ� �Լ�
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



// RB Ʈ�� ��ġ ȸ�� �Ϲ�ȭ
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

// RB Ʈ�� ���� �Ϲ�ȭ
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

			// 1. �� �����ߴµ�, ���尡 ��������
			if (parent->red) {
				gparent->red = 1;
				if ((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
					parent = (RBtree*)gen_rotate(key, gparent, base, num, sizeof(wcount), wcount_cmp);
				t = (RBtree*)gen_rotate(key, ggparent, base, num, sizeof(wcount), wcount_cmp);
				t->red = 0;
			}
			base->left->red = 0;
		}

		// ȸ�� ���� ���� ���� ����
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (fcmp(key, t + 1) < 0) t = t->left;
		else t = t->right;
	}

	// ���ο� �� ����
	t = (RBtree*)malloc(sizeof(RBtree) + width);
	memcpy(t + 1, key, width);
	t->left = NULL;
	t->right = NULL;
	if ((fcmp(key, parent + 1) < 0) || parent == base) parent->left = t;
	else parent->right = t;

	(*num)++; // ������ ���� �ϳ� �÷��ֱ�
	t->red = 1; // ���Ӱ� �����ϴ� ���� ����

	// 2. �׳� �����ߴµ� ���尡 ��������
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

// RB Ʈ�� Ž�� �Լ�, ���� Ʈ�� Ž�� �Լ��� ����
void* btv_search(void* key, RBtree* base, int* num, int width, FCMP fcmp)
{
	RBtree* s;
	s = base->left;

	while (s != NULL && fcmp(key, s + 1) != 0) { // ����Ʈ�� ����Ʈ�� �ִ� ���� �ǳʶٰ� �� ���� ���� ��
		if (fcmp(key, s + 1) < 0) // ã�� ���� ���ϴ� ������ ������
			s = s->left; // �������� �̵�
		else // ã�� ���� ���ϴ� ������ ũ��
			s = s->right; // ���������� �̵�
	}

	if (s == NULL) return NULL; // �� ã���� ��
	else return s + 1; // ã���� �� ���� �ּ� ��ȯ
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
				seed_parent = parent; /* ���� ��峪 ������ �ڽ��� ���� ��� ã�� */
			parent = del;
			del = del->left;
		}
		else
		{
			if (del->red || (del->left && del->left->red))
				seed_parent = parent; /* ���� ��峪 ���� �ڽ��� ���� ��� ã�� */
			parent = del;
			del = del->right;
		}
	}

	return seed_parent;
}

void make_leaf_red(int key, RBtree* base)
{
	RBtree* seed_parent, * seed, * seed_child;

	seed_parent = find_seed(key, base); /* ���� ������ ã�� */

	if (seed_parent == NULL) /* ���� ������ ������ */
	{
		seed_parent = base;
		seed = seed_parent->left;
		seed->red = 1; /* �Ѹ���带 �������� �ϰ� �������� ��´� */
	}
	else
	{
		if (key < seed_parent->key || seed_parent == base)
			seed = seed_parent->left;
		else
			seed = seed_parent->right;
	}

	if (!seed->red) /* ������ ������ �ƴϸ� �� �ڽ��� �����̴� */
	{/* �׷��� ȸ���� �Ͽ� ������ ���� �ø��� */
		if (key < seed->key)
			seed_child = seed->right;
		else
			seed_child = seed->left;

		seed->red = 1;
		seed_child->red = 0;
		seed_parent = rotate(seed_child->key, seed_parent, base); /* ȸ�� */
	}

	while (seed->left && seed->right)
	{/* �ܺ� ��尡 �ƴ� ���� */
		seed->red = 0; /* ������ ��ȯ */
		seed->right->red = seed->left->red = 1;
		if (key < seed->key)
		{
			if ((seed->right->left || seed->right->right) && (seed->right->left->red || seed->right->right->red))
			{   /* ȸ���� �ʿ��ϸ� ȸ���� �Ѵ� */
				if (seed->right->left && seed->right->left->red)
				{/* RLȸ���� �ʿ� */
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
			{/* ȸ���� �ʿ��ϸ� ȸ���� �Ѵ� */
				if (seed->left->right && seed->left->right->red)
				{/* LRȸ���� �ʿ� */
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
		/* ������ Ű�� ã�� */
		parent = del;
		if (key < del->key)
			del = del->left;
		else
			del = del->right;
	}
	if (del == NULL)
		return NULL; /* ������ Ű�� ã�� ���� */

	if (del->right && del->left)
	{

		/* �ڽ��� �� ���̸�, �� ���� ����̸� */
		pcenter = del; /* ������ ��带 ��ü�� ��带 ã�� */
		center = del->right;

		while (center->left != NULL)
		{
			pcenter = center;
			center = center->left; /* center�� ��ü�� Ű�� */
		}

		del->key = center->key; /* ������ Ű�� ��ü�� Ű�� �ٲ� */
		del = center; /* ���� center�� �����ϵ��� ���� */
		parent = pcenter;
		key = del->key;
	}

	if (del->left || del->right)
	{

		/* �ڽ��� �ϳ��� ���, �ڽ��� �ϳ��� �ݵ�� ���� �ڽ��̴� */
		if (del->left)
			son = del->left;
		else
			son = del->right;

		son->red = 0;
	}
	else if (del->left == NULL && del->right == NULL)
	{

		/* �ڽ��� ���� ���, �����̸� �׳� ����, �����̸� 2-����̹Ƿ� 3-��峪 4-���� ��ȯ �Ŀ� ����*/
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

