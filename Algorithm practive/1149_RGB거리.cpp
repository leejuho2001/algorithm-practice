#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1149_RGB�Ÿ� ----

	���� : �����ִ� ������ �ٸ� �����ϰ�
	�� ������ ���� ���� ����� ����.

	���̵�� : �� ���� ���󸶴� �ּ� ����� ������.
	�ּ� ����� ���� �ʴ´ٸ� �ٷ� Ž���� �ߴ��ϴ� ���� ����.
	���� �̸� �̿��� Ž�� �˰����� ������ �� ����.

	�ٽ� ���� : ������ ������ ���� ���� ������ ���ϴ� ����(compare)
	�ش� ������ ����Ǵ� Ƚ�� : 6 * n = 6n(�ִ� 6000)
	�ð����⵵ : O(n)
*/


#include<iostream>
using namespace std;
#define inf 12345678

#define R 0
#define G 1
#define B 2

int n;

int houseCost[1050][3];
int costList[1050][3];

/*
	---- input ----
	�Է� : ����
	�ൿ : n�� �� house�� cost�� ����.
*/

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> houseCost[i][R] >> houseCost[i][G] >> houseCost[i][B];
}

/*
	---- costListInit ----
	�Է� :����
	��� : index�� 0�� �κ��� ������ ��� index�� ���� inf�� �ʱ�ȭ 
*/

void costListInit() {
	costList[0][R] = 0;
	costList[0][G] = 0;
	costList[0][B] = 0;

	for (int i = 1; i <= n; i++) {
		costList[i][R] = inf;
		costList[i][G] = inf;
		costList[i][B] = inf;
	}
}


/*
	---- greedy ----
	�Է� : ����
	�ൿ : costList�� ���ʱ�ȭ�� ���� Ž�� �˰����� ������.
	�� �ܰ��� �ּڰ��� ������ ����, �� �ּڰ����� ������ ���� ���� ���غ��鼭 �ּڰ��̸� ����.
	�� ������ n���� �ݺ�
*/


int greedy() {
	for (int i = 1; i <= n; i++) {
		if (costList[i - 1][R] + houseCost[i][G] < costList[i][G])
			costList[i][G] = costList[i - 1][R] + houseCost[i][G];

		if (costList[i - 1][R] + houseCost[i][B] < costList[i][B])
			costList[i][B] = costList[i - 1][R] + houseCost[i][B];

		if (costList[i - 1][G] + houseCost[i][R] < costList[i][R])
			costList[i][R] = costList[i - 1][G] + houseCost[i][R];

		if (costList[i - 1][G] + houseCost[i][B] < costList[i][B])
			costList[i][B] = costList[i - 1][G] + houseCost[i][B];

		if (costList[i - 1][B] + houseCost[i][R] < costList[i][R])
			costList[i][R] = costList[i - 1][B] + houseCost[i][R];

		if (costList[i - 1][B] + houseCost[i][G] < costList[i][G])
			costList[i][G] = costList[i - 1][B] + houseCost[i][G];
	}

	int result = inf;
	if (result > costList[n][R]) result = costList[n][R];
	if (result > costList[n][G]) result = costList[n][G];
	if (result > costList[n][B]) result = costList[n][B];

	return result;
}

int main() {
	input(); 
	costListInit();
	int result = greedy();

	cout << result;
}

