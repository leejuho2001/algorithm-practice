/*
	---- 17404_RGB거리 2 ----
	RGB거리와의 차이점 : 1번 집과 n번 집의 컬러가 달라야 한다는 조건이 추가됨.

	--> R로 시작한 경우, G로 시작한 경우, B로 시작한 경우로 나누어
	나올 수 있는 6가지의 최솟값을 모두 구한 뒤, 비교해주면 됨.

	시작한 경우를 표현하는 법:
	1번째 선택에서 R값만 제대로 주고 나머지 inf : R로 시작
	이런 방식으로 시작 지점을 강제함.

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
	//시작 지점 강제 부분
}


/*
	---- greedy ----
	입력 : 없음
	행동 : costList의 재초기화를 통해 탐욕 알고리즘을 시행함.
	각 단계의 최솟값을 저장해 놓고, 각 최솟값에서 가능한 색상에 대해 더해보면서 최솟값이면 대입.
	이 과정을 n까지 반복
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