#define _CRT_SECURE_NO_WARNINGS

/*
	---- 9465_��ƼĿ ----

	���̵�� : 2*n ũ���� array�� ���� Ž��
	
	n��° ��ġ k�� ��ƼĿ�� ��´ٰ� ���������� ������ ��� : 2����
	
	n-1��°, k�� �ݴ� ��ġ
	n-2��°, k�� �ݴ� ��ġ
	
	-> n-2��° k��ġ������ �ִ� + n-1��°, k�� �ݴ� ��ġ = n-1��°, k�� �ݴ� ��ġ������ �ִ��̱⶧��.

	�ش� �ΰ��� ��츦 ���Ͽ� ���� ���ϸ� �� : greedy�� ����� �� ����.
	*/

#include<stdio.h>

int n;
int sticker[100050][2];
int results[100050][2];

int max(int a, int b) {
	return a > b ? a : b;
}


void greedy() {
	for (int i = 0; i <= n; i++) {
		if (i == 0) {
			results[i][0] = 0;
			results[i][1] = 0;
			continue;
		}

		if (i == 1) {
			results[i][0] = sticker[i][0];
			results[i][1] = sticker[i][1];
			continue;
		}

		results[i][0] = max(results[i - 1][1], results[i - 2][1]) + sticker[i][0];
		results[i][1] = max(results[i - 1][0], results[i - 2][0]) + sticker[i][1];
	}
}

int main() {
	int nn; scanf("%d", &nn);
	for (int _ = 0; _ < nn; _++) {
		scanf("%d", &n);

		for (int i = 0; i < 2; i++) {
			for (int k = 1; k <= n; k++) scanf("%d", &sticker[k][i]);
		}

		greedy();

		printf("%d", max(results[n][0], results[n][1]));
	}
}