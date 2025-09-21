#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11049_��� ���� ����----

	::DP�� �����.
	DP[i][q] : i��° ��ĺ��� q��° ��ı����� ��İ� �� �ּҸ� ��ȯ
	���� DP[i][i] = 0
	DP[i][i+1]�� ���� �ٷ� ������.

	���̸� 1�� �÷������鼭 ������ �б������� ��� üũ, min���� üũ��.
*/
#define uBound 2147483647;
#include<stdio.h>


typedef struct matrixSize {
	int row;
	int column;
}matSiz;
int DT[505][505];
matSiz sizes[505];

int get_cnt(int s, int m, int e) {
	return sizes[s].row * sizes[m].column * sizes[e].column;
}

int main() {
	int n; scanf("%d", &n);
	int MAX = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &sizes[i].row, &sizes[i].column);
		if (i > 1)
			DT[i - 1][i] = get_cnt(i - 1, i - 1, i);
	}

	for (int i = 2; i < n; i++) {
		for (int q = 1; q <= n - i; q++) {
			MAX = uBound;
			//DT[q][q+i] �� ���� �ٷ�.
			for (int z = 0; z < i; z++) {
				int curr = DT[q][q + z] + DT[q + z + 1][q + i] + get_cnt(q, q + z, q + i);
				
				if (curr < MAX) MAX = curr;
			}
			DT[q][q + i] = MAX;
		}
	}

	printf("%d", DT[1][n]);
}