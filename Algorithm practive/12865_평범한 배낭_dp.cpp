#define _CRT_SECURE_NO_WARNINGS
/*
	---- 12865_����� �賶_dp ----

	DP�� �ذ���.
	x, y : x��° �����۱��� + y���Ա��� ���� �� ����.
	����, ����� �� �ΰ���
	1. x��° �������� �ȳ��� �ִ� 
	2. x��° �������� ���� �ִ�

	2�� ������ ���ؼ� x��° �������� ���Ը�ŭ ��ĭ�� Ȯ���Ǿ�� �ϹǷ�,
	x-1��° �����۱���, y���� x��° ���Ը� ������ ���Ա��� ���� �� ����.
	�� ���ϸ� �ذ��.

	x��° ���� x��° �������� ������ ������ ��ŭ,
	x��° �������� ���Ժ��� ���� y���� ���� ���, 2�� ���� 0�� ��.

*/



#include<stdio.h>

int DT[105][100005];

int n, w, v, k;
typedef struct _item {
	int weight;
	int value;
}item;

item items[105];

void itemInput() {
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &items[i].weight, &items[i].value);
	}
}

int bigger(int a, int b) {
	return a > b ? a : b;
}

void DP() {

	for (int i = 1; i <= n; i++) {
		int ItemW = items[i].weight;
		int ItemV = items[i].value;

		for (int q = 1; q <= k; q++) {
			if (q < ItemW) DT[i][q] = bigger(DT[i - 1][q], 0);
			else DT[i][q] = bigger(DT[i - 1][q], DT[i - 1][q - ItemW] + ItemV);
		}
	}

}


int main() {
	scanf("%d %d", &n, &k);
	itemInput();

	DP();
	printf("%d", DT[n][k]);
}