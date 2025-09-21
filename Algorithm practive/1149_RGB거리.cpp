#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1149_RGB거리 ----

	조건 : 옆에있는 집과는 다른 색상일것
	각 집마다 색상에 따른 비용이 있음.

	아이디어 : 각 집과 색상마다 최소 비용이 존재함.
	최소 비용이 되지 않는다면 바로 탐색을 중단하는 것이 가능.
	따라서 이를 이용해 탐욕 알고리즘을 시행할 수 있음.

	핵심 연산 : 설정된 값보다 현재 값이 작은지 비교하는 연산(compare)
	해당 연산이 실행되는 횟수 : 6 * n = 6n(최대 6000)
	시간복잡도 : O(n)
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
	입력 : 없음
	행동 : n과 각 house의 cost를 받음.
*/

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> houseCost[i][R] >> houseCost[i][G] >> houseCost[i][B];
}

/*
	---- costListInit ----
	입력 :없음
	결과 : index가 0인 부분을 제외한 모든 index의 값을 inf로 초기화 
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
	입력 : 없음
	행동 : costList의 재초기화를 통해 탐욕 알고리즘을 시행함.
	각 단계의 최솟값을 저장해 놓고, 각 최솟값에서 가능한 색상에 대해 더해보면서 최솟값이면 대입.
	이 과정을 n까지 반복
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

