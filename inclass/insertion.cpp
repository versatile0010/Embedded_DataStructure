/*
		Insertion (���� ����) , big-O notation : O(N^2)
	
		ȿ���� ����
		quick sort���� ����� �� ���� �� ��õ��

		�ٸ� Worst Case ( Revese )�� ��� �������ĺ��� ȿ���� �����ʴ�.
		������ ����(Half-sorted)�� ��쿡�� ��û ��������.

*/

void insert_sort(int* a, int N) {
	int i, j, t;
	/*
		�� �������� a[i]��ſ� t�� ���� ����ұ�?

			-> a[i]�� ����ϸ� �����Ϸ��� �޸𸮸� access�Ѵ�
			-> *(a+i)
			-> �׳� t�� variable�� ��� ���°� ������.
			-> �Ӻ���� ȯ�濡�� �˰����� ������ �� ����.
	*/
	for (i = 1; i < N; i++) {
		t = a[i];
		j = i;
		while (j > 0 && a[j-1] > t) {	// Stability : ���� ���� �� ������ �����ϴ���
			a[j] = a[j - 1];			// insertion sort�� stability ����
			j--;
		}
		a[j] = t;
	}
}

// Optimization�� ���� ���� sort�� ���ָ� ����.
// ���� �����͸� �����ؾ� �ϴ� ��찡 ����.
// ������ Index ������.
void indirect_insert_sort(int* a, int* index, int N) {
	int i, j, t;
	for (i = 0; i < N; i++) {
		index[i] = i;
	}
	for (i = 1; i < N; i++) {
		t = index[i];
		j = i;
		while (j > 0 && a[index[j-1]] > a[t]) {
			index[j] = index[j - 1];
			j--;
		}
		index[j] = t;
	}
}

void insert_sort(void* base, int nelem, int width, int (*fcmp)(const void*, const void*)) {
	int i, j;
	void* t;

	//	Assignment

}