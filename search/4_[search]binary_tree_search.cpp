#include "ds.h"

/*
*	Binary tree search 2022. 05.25
*/

double_node* bti_search(int key, double_node* base, int* num)
{
	double_node* s;
	s = base->left; // s is a root node
	while (key != s->key && s != NULL)
	{
		if (key < s->key)
			s = s->left;
		else
			s = s->right;
	}
	if (s == NULL) return NULL;
	else return s; // return a target node
}

double_node* bti_insert(int key, double_node* base, int* num)
{
	double_node* p, * s;
	p = base; // �ʱ⿡�� base �� left right �� �� null
	s = base->left;

	while (s != NULL)
	{
		p = s;
		if (key < s->key) s = s->left;
		else s = s->right;
	}
	s = (double_node*)malloc(sizeof(double_node));
	s->key = key;

	s->left = NULL;
	s->right = NULL;
	
	if (key < p->key || p == base) p->left = s;
	else p->right = s;
	(*num)++;
	return s;
}
/*
	( lecture note slide 5 )
	  case 1. external node �� ��� �׳� memory deallocating ���ְ�, ����ƾ��� �θ� ������ edge �� NULL �� ����

	  case 2. one chile  ( L - M - N ���� M �����ϴ� ��� )
			  : L �� N ���� �������ְ� M �� memory �� deallocating.

	  case 3. child node is full ( != root node )
			 ( ���� ��� B -> left : A, B-> right : D �� ��� B �� �����ϰ��� �ϴ� ���. )
			  : �׻� parent node �� left child ���� Ŀ�� �Ѵٴ� �Ϳ� ����!
			    �Ϲ������� child node �� larger node �� ���� �ø���.
				��� D �� parent �� ����� ( F -> left = D )
				D �� left �� A, right �� NULL

	  case 4. delete root node
			  : �ִ��� ������ topology �� �����ϸ鼭 delete ����.
			    ROOOT node �� �ִ��� ����� node �� �ø���.
				right side ���� ���� left node �� root �� ��ü����.
				�׸��� base �� �����Ѵ�.
*/

double_node* bti_delete1(int key, double_node* base, int* num)
{
	double_node* parent, * son, * del, * nexth;
	// parent : parent of del	son : child of parent	del : delete node	nexth : parent of son
	parent = base;
	del = base->left;
	// first we have to search
	while (key != del->key && del != NULL) {
		parent = del;
		if (del->key > key) del = del->left;
		else del = del->right;
	}
	if (del == NULL) return NULL; // can't find

	if (del->left == NULL && del->right == NULL)
	{
		// CASE [1] : External node
		son = NULL; // Parent �� son �� null ��
	}
	else if (del->left != NULL && del->right != NULL)
	{
		// CASE [3]
		nexth = del->right;
		if (nexth->left != NULL) // CASE [4] : root node
		{
			while (nexth->left->left != NULL) nexth = nexth->left;
			son = nexth->left;
			// ���� son �� root ���� �ø���.
			nexth->left = son->right; // son �� ������踦 ����,
			son->left = del->left; // ���� root node(del) �� �ڽĵ�� ����
			son->right = del->right;
		}
		else // CASE [3] : isn't root node
		{
			son = nexth;
			son->left = del->left;
		}
	}
	else // case [2] : one child
	{
		if (del->left != NULL) son = del->left;
		else son = del->right;
	}

	// ���� parent �� son �� ���� (ground rule �� ����)
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;
	
	free(del); // ����
	(*num)--; // node ���� ����

	return parent; // delete node �� parent node �� return ��.
}


double_node* bti_delete(int key, double_node* base, int* num) // modified version
{
	// case �� 1. no right child   2.  no right->left child   3. otherwise  �� �з���
	// more simple!

	// first we have to search del node
	double_node* parent, * son, * del, * nexth;
	// parent : parent of del	son : child of parent(del)	del : delete node	nexth : parent of son
	parent = base;
	del = base->left;

	while (key != del->key && del != NULL) {
		parent = del;
		if (del->key > key) del = del->left;
		else del = del->right;
	}

	if (del->right == NULL) son = del->left;
	else if (del->right->left == NULL)
	{
		son = del->right;
		son->left = del->left;
	}
	else
	{
		nexth = del->right;
		while (nexth->left->left != NULL) nexth = nexth->left;
		son = nexth->left;
		
		nexth->left = son->right;
		son->left = del->left;
		son->right = del->right;
	}

	// ���� parent �� son �� ���� (ground rule �� ����)
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;

	free(del); // ����
	(*num)--; // node ���� ����

	return parent; // delete node �� parent node �� return ��.
}

// LEC 13 PAGE
// base->left �� f ��
// base->left->right->left->left->key : G


/*=====================================================================================
*		
*		Improved version of Binary Tree Search 2022. 05. 30.
* 
*					A - B - C						A
*												  /   |
*												B      C
*				 < Unbalanced >				 < Balanced >
* search cost			O(N)		>			O(logN)
* 
* How to make tree balance?
* �����ڷ� 5 ������
* Using Inorder traverse method ! ( visiting order : left subtree -> root -> right subtree
* : A B C D F G H K L M N O 
* inorder traverse �� �����ν� sorting �ȴ�.
* ==================================================================================== */


// p : original tree
void bti_sort(double_node* p, int* a, int* index)
{
	if (p != NULL)
	{
		bti_sort(p->left, a, index);
		a[(*index)++] = p->key; // sorted array 
		bti_sort(p->right, a, index);
	}
}

double_node* _balance(int N, int* a, int* index)
{
	// To make a balanced tree, 
	// 1. Sort a given tree ( using inorder traverse)
	// 2. Codunct _balance
	int nl, nr;
	double_node* p; // balanced tree �� ������ p

	if (N > 0)
	{
		nl = (N - 1) / 2;
		nr = N - nl - 1; // except root

		p = (double_node*)malloc(sizeof(double_node));
		p->left = _balance(nl, a, index);
		p->key = a[(*index)++];
		p->right = _balance(nr, a, index);
	
		return p;
	}
	else return NULL;
}

void btiprint(double_node* p) {
	double_node* pl, * pr;
	if (p->left != NULL && p->right != NULL) { // fully 
		printf("\n%c child :", p->key);
		printf("left: %c / right : %c\n", p->left->key, p->right->key);
		pl = p->left;
		pr = p->right;
		btiprint(pl);
		btiprint(pr);
	}
	else if (p->left == NULL && p->right != NULL) { // has a child
		printf("\n%c child :", p->key);
		printf("left : NULL / right : %c\n", p->right->key);

		pr = p->right;
		btiprint(pr);
	}
	else if (p->left != NULL && p->right == NULL) { // external node
		printf("\n%c child :", p->key);
		printf("left : %c / right : NULL\n", p->left->key);

		pl = p->left;
		btiprint(pl);
	}
	else return;
}