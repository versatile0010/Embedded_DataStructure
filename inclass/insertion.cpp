/*
		Insertion (삽입 정렬) , big-O notation : O(N^2)
	
		효율이 좋다
		quick sort등을 사용할 수 없을 때 추천됨

		다만 Worst Case ( Revese )의 경우 선택정렬보다 효율이 좋지않다.
		적당히 정렬(Half-sorted)된 경우에는 엄청 빨라진다.

*/

void insert_sort(int* a, int N) {
	int i, j, t;
	/*
		왜 쓸데없이 a[i]대신에 t를 굳이 사용할까?

			-> a[i]를 사용하면 컴파일러가 메모리를 access한다
			-> *(a+i)
			-> 그냥 t에 variable로 담아 놓는게 빠르다.
			-> 임베디드 환경에서 알고리즘을 구현할 때 좋다.
	*/
	for (i = 1; i < N; i++) {
		t = a[i];
		j = i;
		while (j > 0 && a[j-1] > t) {	// Stability : 값이 같을 때 순서를 보존하는지
			a[j] = a[j - 1];			// insertion sort는 stability 만족
			j--;
		}
		a[j] = t;
	}
}

// Optimization을 위해 간접 sort를 해주면 좋다.
// 원본 데이터를 보존해야 하는 경우가 많다.
// 순서를 Index 해주자.
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