#include "ds.h"

int seq_search(int key, int* a, int* num)
{
	int i = 0;
	while (a[i] != key && i < *num) i++;

	return (i < *num ? i : -1); //return the index
}

int seq_insert(int key, int* a, int* num)
{
	a[(*num)++] = key;

	return (*num) - 1; // �迭�� �� index
}

int seq_delete(int key, int* a, int* num)
{
	int p, i;
	if (*num > 0)
	{
		if ((p = seq_search(key, a, num)) < 0) return -1; // ã�����ϸ� 
		for (i = p + 1; i < *num; i++) // ã������
		{
			a[i - 1] = a[i]; // �ڿ��� ������ �� �о������
			//memcpy
		}
		(*num)--; // ���� �ϳ� ����
		return p;
	}
	return -1;
}

// Improvement with hit rates(preference).
// time to market
int seq_f_search(int key, int* a, int* num)
{
	int p, i;
	if ((p = seq_search(key, a, num)) < 0)
		return -1;
	for (i = p - 1; i >= 0; i--)
		a[i + 1] = a[i];
	a[0] = key;
	// ã�� key �� �Ǿ����� �ű��, �������� �ڷ� �δ�.
	// user �� preference �ݿ�
	return 0;
}


int lv_search(void* key, void* base, int* num, int width, FCMP fcmp)
{
	int i = 0;
	while (fcmp(BASE(i), key) != 0 && i < *num)i++;
	return (i < *num ? i : -1);
}

int lv_insert(void* key, void* base, int* num, int width, FCMP fcmp)
{
	memcpy(BASE((*num)++), key, width);
	return *num - 1;
}

int lv_delete(void* key, void* base, int* num, int width, FCMP fcmp)
{
	int p, i;
	if (*num > 0)
	{
		if ((p = lv_search(key, base, num, width, fcmp)) < 0) return -1;
		for (i = p + 1; i < *num; i++)
		{
			memcpy(BASE(i - 1), BASE(i), width);
		}
		(*num)--;
		return p;
	}
	return -1;
}

int lfv_search(void* key, void* base, int* num, int width, FCMP fcmp)
{
	int i = 0, j;
	void* v; // temp
	while (fcmp(BASE(i), key) != 0 && i < *num) i++;
	if (i >= *num) return -1; // fail to search
	v = malloc(width);
	memcpy(v, BASE(i), width);
	for (j = i - 1; j >= 0; j--)
		memcpy(BASE(i + 1), BASE(i), width);
	memcpy(BASE(0), v, width);
	return 0;
}
