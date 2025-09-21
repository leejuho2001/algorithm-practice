#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1041_�ֻ��� ----

	2 �̻��� ���̸� ���� �ֻ����� ������ �� �� �鿡 ���̴� �ֻ����� ������ ������ ����.

	1. �� ���� ���̴� �ֻ��� : 4��
	2. �� ���� ���̴� �ֻ��� : (n-1)*4 + (n-2)*4 ��
	3. �� ���� ���̴� �ֻ��� : (n-2)*(n-1)*4 + (n-2)^2 ��

	���⼭ �� ���� �׳� �ּҰ�,
	�� ���� �� ���������� ������ �� ���� �� �� ���� ū ���� �� ��,
	�� ���� �� ���������� ������ �� ���� ���� ����ϸ�,

	�̵� �� �ּڰ��� ����Ͽ� ����Ѵ�.

	�ִ� 15�ڸ��� ���� �� �����Ƿ�, ����� longlongint�� ����Ͽ� ǥ���Ѵ�.
	*/

#include<stdio.h>
#include<algorithm>
using namespace std;

long long int dice[7];
long long int n;
int main() {
	scanf("%d", &n);
	int v[8][3] = { {1, 2, 3},{1, 2, 4},{1, 4, 5},{1, 3, 5},{6, 2, 3},{6, 2, 4},{6, 4, 5},{6, 3, 5} };

	for (int i = 1; i <= 6; i++) {
		scanf("%d", dice + i);
	}
	long long int val3 = 12345678, val2 = 12345678;
	
	for (int i = 0; i < 8; i++) {
		if (val3 > dice[v[i][0]] + dice[v[i][1]] + dice[v[i][2]])
			val3 = dice[v[i][0]] + dice[v[i][1]] + dice[v[i][2]];

		if (val2 > dice[v[i][0]] + dice[v[i][1]])
			val2 = dice[v[i][0]] + dice[v[i][1]];

		if (val2 > dice[v[i][1]] + dice[v[i][2]])
			val2 = dice[v[i][1]] + dice[v[i][2]];

		if (val2 > dice[v[i][0]] + dice[v[i][2]])
			val2 = dice[v[i][0]] + dice[v[i][2]];
	}

	sort(dice+1, dice+7);
	long long int res;
	if (n == 1) {
		res =  dice[5] + dice[1] + dice[2] + dice[3] + dice[4];
	}

	else if (n == 2) {
		res =  val3 * 4 + val2 * 4;
	}

	else res =  val3 * 4 + val2 * ((n - 1) * 8 - 4) + dice[1] * ((n - 2) * (n - 1) * 4 + (n - 2) * (n - 2));
	printf("%lld", res);

}
