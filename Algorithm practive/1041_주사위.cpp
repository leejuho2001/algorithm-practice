#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1041_주사위 ----

	2 이상의 길이를 가진 주사위를 구성할 때 각 면에 보이는 주사위의 구성은 다음과 같다.

	1. 세 면이 보이는 주사위 : 4개
	2. 두 면이 보이는 주사위 : (n-1)*4 + (n-2)*4 개
	3. 한 면이 보이는 주사위 : (n-2)*(n-1)*4 + (n-2)^2 개

	여기서 한 면은 그냥 최소값,
	두 면은 한 꼭짓점에서 만나는 세 면의 합 중 가장 큰 수를 뺀 값,
	세 면은 한 꼭짓점에서 만나는 세 면의 합을 사용하며,

	이들 중 최솟값을 사용하여 계산한다.

	최대 15자리가 나올 수 있으므로, 결과는 longlongint를 사용하여 표현한다.
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
