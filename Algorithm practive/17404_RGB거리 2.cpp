/*
	---- 17404_RGB�Ÿ� 2 ----
	RGB�Ÿ����� ������ : 1�� ���� n�� ���� �÷��� �޶�� �Ѵٴ� ������ �߰���.

	--> R�� ������ ���, G�� ������ ���, B�� ������ ���� ������
	���� �� �ִ� 6������ �ּڰ��� ��� ���� ��, �����ָ� ��.

	������ ��츦 ǥ���ϴ� ��:
	1��° ���ÿ��� R���� ����� �ְ� ������ inf : R�� ����
	�̷� ������� ���� ������ ������.

*/

#include<iostream>
using namespace std;
#define inf 12345678

#define R 0
#define G 1
#define B 2

int n;

int houseCost[1050][3];
int costListR[1050][3];
int costListG[1050][3]; 
int costListB[1050][3];

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
	

	for (int i = 1; i <= n; i++) {
		for (int q = 0; q < 3; q++) {
			costListR[i][q] = inf;
			costListG[i][q] = inf;
			costListB[i][q] = inf;
		}
	}

	costListR[1][R] = houseCost[1][R];
	costListR[1][G] = inf;
	costListR[1][B] = inf;
	costListG[1][R] = inf;
	costListG[1][G] = houseCost[1][G];
	costListG[1][B] = inf;
	costListB[1][R] = inf;
	costListB[1][G] = inf;
	costListB[1][B] = houseCost[1][B];
	//���� ���� ���� �κ�
}


/*
	---- greedy ----
	�Է� : ����
	�ൿ : costList�� ���ʱ�ȭ�� ���� Ž�� �˰����� ������.
	�� �ܰ��� �ּڰ��� ������ ����, �� �ּڰ����� ������ ���� ���� ���غ��鼭 �ּڰ��̸� ����.
	�� ������ n���� �ݺ�
*/


int greedy() {
	for (int i = 2; i <= n; i++) {
		if (costListR[i - 1][R] + houseCost[i][G] < costListR[i][G])
			costListR[i][G] = costListR[i - 1][R] + houseCost[i][G];
		if (costListG[i - 1][R] + houseCost[i][G] < costListG[i][G])
			costListG[i][G] = costListG[i - 1][R] + houseCost[i][G];
		if (costListB[i - 1][R] + houseCost[i][G] < costListB[i][G])
			costListB[i][G] = costListB[i - 1][R] + houseCost[i][G];

		if (costListR[i - 1][R] + houseCost[i][B] < costListR[i][B])
			costListR[i][B] = costListR[i - 1][R] + houseCost[i][B];
		if (costListG[i - 1][R] + houseCost[i][B] < costListG[i][B])
			costListG[i][B] = costListG[i - 1][R] + houseCost[i][B];
		if (costListB[i - 1][R] + houseCost[i][B] < costListB[i][B])
			costListB[i][B] = costListB[i - 1][R] + houseCost[i][B];

		if (costListR[i - 1][G] + houseCost[i][R] < costListR[i][R])
			costListR[i][R] = costListR[i - 1][G] + houseCost[i][R];
		if (costListG[i - 1][G] + houseCost[i][R] < costListG[i][R])
			costListG[i][R] = costListG[i - 1][G] + houseCost[i][R];
		if (costListB[i - 1][G] + houseCost[i][R] < costListB[i][R])
			costListB[i][R] = costListB[i - 1][G] + houseCost[i][R];

		if (costListR[i - 1][G] + houseCost[i][B] < costListR[i][B])
			costListR[i][B] = costListR[i - 1][G] + houseCost[i][B];
		if (costListG[i - 1][G] + houseCost[i][B] < costListG[i][B])
			costListG[i][B] = costListG[i - 1][G] + houseCost[i][B];
		if (costListB[i - 1][G] + houseCost[i][B] < costListB[i][B])
			costListB[i][B] = costListB[i - 1][G] + houseCost[i][B];

		if (costListR[i - 1][B] + houseCost[i][R] < costListR[i][R])
			costListR[i][R] = costListR[i - 1][B] + houseCost[i][R];
		if (costListG[i - 1][B] + houseCost[i][R] < costListG[i][R])
			costListG[i][R] = costListG[i - 1][B] + houseCost[i][R];
		if (costListB[i - 1][B] + houseCost[i][R] < costListB[i][R])
			costListB[i][R] = costListB[i - 1][B] + houseCost[i][R];

		if (costListR[i - 1][B] + houseCost[i][G] < costListR[i][G])
			costListR[i][G] = costListR[i - 1][B] + houseCost[i][G];
		if (costListG[i - 1][B] + houseCost[i][G] < costListG[i][G])
			costListG[i][G] = costListG[i - 1][B] + houseCost[i][G];
		if (costListB[i - 1][B] + houseCost[i][G] < costListB[i][G])
			costListB[i][G] = costListB[i - 1][B] + houseCost[i][G];
	}

	int result = inf;
	
	if (result > costListR[n][G]) result = costListR[n][G];
	if (result > costListR[n][B]) result = costListR[n][B];
	if (result > costListG[n][R]) result = costListG[n][R];
	if (result > costListG[n][B]) result = costListG[n][B];
	if (result > costListB[n][R]) result = costListB[n][R];
	if (result > costListB[n][G]) result = costListB[n][G];

	return result;
}

int main() {
	input();
	costListInit();
	int result = greedy();



	cout << result;
}