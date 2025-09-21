#define _CRT_SECURE_NO_WARNINGS
/*
	---- 12865_평범한 배낭_dp ----

	DP로 해결함.
	x, y : x번째 아이템까지 + y무게까지 넣을 수 있음.
	따라서, 경우의 수 두가지
	1. x번째 아이템을 안넣은 최대 
	2. x번째 아이템을 넣은 최대

	2번 구현을 위해선 x번째 아이템의 무게만큼 빈칸이 확보되어야 하므로,
	x-1번째 아이템까지, y에서 x번째 무게를 제외한 무게까지 담을 수 있음.
	을 비교하면 해결됨.

	x번째 열은 x번째 아이템의 유무만 따지는 만큼,
	x번째 아이템의 무게보다 작은 y값을 가질 경우, 2의 값은 0이 됨.

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