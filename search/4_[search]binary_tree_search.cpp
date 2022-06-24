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
	p = base; // 초기에는 base 의 left right 는 다 null
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
	  case 1. external node 인 경우 그냥 memory deallocating 해주고, 연결됐었던 부모 노드와의 edge 를 NULL 로 세팅

	  case 2. one chile  ( L - M - N 에서 M 삭제하는 경우 )
			  : L 을 N 으로 연결해주고 M 의 memory 를 deallocating.

	  case 3. child node is full ( != root node )
			 ( 예를 들어 B -> left : A, B-> right : D 인 경우 B 를 삭제하고자 하는 경우. )
			  : 항상 parent node 가 left child 보다 커야 한다는 것에 유의!
			    일반적으로 child node 중 larger node 를 위로 올린다.
				노드 D 를 parent 로 만들고 ( F -> left = D )
				D 의 left 를 A, right 를 NULL

	  case 4. delete root node
			  : 최대한 원형의 topology 를 유지하면서 delete 하자.
			    ROOOT node 랑 최대한 가까운 node 를 올리자.
				right side 에서 가장 left node 를 root 로 대체하자.
				그리고 base 랑 연결한다.
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
		son = NULL; // Parent 의 son 을 null 로
	}
	else if (del->left != NULL && del->right != NULL)
	{
		// CASE [3]
		nexth = del->right;
		if (nexth->left != NULL) // CASE [4] : root node
		{
			while (nexth->left->left != NULL) nexth = nexth->left;
			son = nexth->left;
			// 이제 son 을 root 노드로 올린다.
			nexth->left = son->right; // son 의 연결관계를 끊고,
			son->left = del->left; // 원래 root node(del) 의 자식들과 연결
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

	// 이제 parent 와 son 을 연결 (ground rule 에 따라서)
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;
	
	free(del); // 삭제
	(*num)--; // node 개수 감소

	return parent; // delete node 의 parent node 를 return 함.
}


double_node* bti_delete(int key, double_node* base, int* num) // modified version
{
	// case 를 1. no right child   2.  no right->left child   3. otherwise  로 분류함
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

	// 이제 parent 와 son 을 연결 (ground rule 에 따라서)
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;

	free(del); // 삭제
	(*num)--; // node 개수 감소

	return parent; // delete node 의 parent node 를 return 함.
}

// LEC 13 PAGE
// base->left 가 f 임
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
* 강의자료 5 페이지
* Using Inorder traverse method ! ( visiting order : left subtree -> root -> right subtree
* : A B C D F G H K L M N O 
* inorder traverse 를 함으로써 sorting 된다.
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
	double_node* p; // balanced tree 를 저장할 p

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