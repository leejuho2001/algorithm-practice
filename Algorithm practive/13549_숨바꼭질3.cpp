#define _CRT_SECURE_NO_WARNINGS

/*
	---- 13549_���ٲ��� 3 ----

	���̵��:
	0. DFS�� ����Ͽ� Ž���Ѵ�. 
	1. �����̿� ������ �Ÿ��� �ּ��� �� �ΰ� �����Ѵ�.
	2. x+1�� ���� x-1��, x-1�� ���� x+1�� ���� ���ϵ��� ������ ������ ���� Ž���� ������ ���� ������ �����Ѵ�.
	3. Ž��Ƚ���� �ִ�Ƚ���� �Ѿ�ų�, �������� �����ϸ� Ž���� �ߴ��Ѵ�.
	4. ������ ��ġ�� �������� Ŭ ���, ������ x-1�� Ž���Ѵ�

*/


#include<stdio.h>


int N, K;
int min = 12345678;
int minarr[10000000];

/*
	---- DFS ----
	:: param ::
	_level : ������� �����̰� �̵��� Ƚ��(Ž���� ����)
	_n : ������ ��ġ
	_k : ������ ��ġ
	type : ���� Ž���� ����


	������ ����
	1: ���� Ž������ x+1�� �̵���.
	-1: ���� Ž������ x-1�� �̵���
	0: ���� Ž������ x*2�� �̵��� or �ʱ����

	x+1�� �� ����
	n�� k���� ������.

	x-1�� �� ����
	: n�� 0���� Ŭ��.
	n�� 2*k�� �Ѿ�� ����.

	2�� �� ����
	: n�� 0���� ũ�� k���� ������.

	��������
	level�� minarr�� ����� ������ ũ�ų� �������
	�ش� ������ ����������� :: min���� �ٽ� �ʱ�ȭ.


	*/

void DFS(int _level, int _n, int _k, int _type) {
	int n = _n;
	int k = _k;
	int level = _level;
	int type = _type;
	//printf("%d %d %d\n", level, n, k);

	if (level < minarr[n]) minarr[n] = level;
	if (level>minarr[n]) return;

	if (n == k) {
		return;
	}

	if (n < k) DFS(level + 0, n * 2, k, 0);

	if (n < k && _type >= 0) {
		DFS(level + 1, n + 1, k, 1);
	}

	if (n>k/2 && n<3*k/2 && _type <= 0) {
		DFS(level + 1, n - 1, k, -1);
	}

}

void init() {
	for (int i = 0; i < K + 10; i++) {
		minarr[i] = 12345678;
	}
}


int main() {
	scanf("%d %d", &N, &K);
	init();
	DFS(0, N, K, 0);

	printf("%d", minarr[K]);
}
