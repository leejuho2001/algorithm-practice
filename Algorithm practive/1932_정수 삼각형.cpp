#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1932_���� �ﰢ�� ----

	���̵�� : �� �������� �� ū�� �÷����鼭 ���Ѵ�.
	n�� ���� ��, ���� �ִ� ������ n^2/2, �ٽ� ������ �񱳿����� �� �ѹ� ����.
	���� �ð����⵵�� O(n^2).

	1. �� �Ʒ� - 1 ������ ������.
	n��° ���Ҵ� n, n+1�� DT + �ش� DT�� �ش��ϴ� �ﰢ���� ���Ұ��� ���� ���Ͽ� �ø�.
	1������ �ݺ�
*/



#include<stdio.h>

int triangle[550][550]; // ���� �����
int DT[550][550];		// DP�� ���� ���̺�

int n;

//�� ū ����� ��ȯ��
int biggerValue(int _valA, int _valB) {
	return _valA > _valB ? _valA : _valB;
}

//���̳��� ���α׷���
int DP() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			DT[i][j] = biggerValue(DT[i + 1][j] + triangle[i + 1][j], DT[i + 1][j + 1] + triangle[i + 1][j + 1]);
		}
	}

	return DT[0][0];
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) scanf("%d", &triangle[i][j]);
	}

	DP();
	printf("%d", DP()+triangle[0][0]);
}