#define _CRT_SECURE_NO_WARNINGS

/*
	---- 7579_앱 ----
	
	기본 아이디어 : 비용 당 확보할 수 있는 바이트 수를 기준으로 정렬함.
	비용이 0일 경우, INF로 취급.(INF = 11111111) 

	비용 당 바이트 수가 같을 경우, 비용이 작은 순서대로 정렬.
	기본적인 골자는 snapsack 문제와 같음.
	가장 적은 비용으로 가장 많은 용량을 차지하되, snapsack 문제와 다른 점은 비용의 합이
	주어진 합보다 더 커야만 한다는 것.
	DT의 크기는 앱의 개수인 n * 앱의 최대크기 * 앱의 개수인 100n
	따라서 최대 크기는 100 * 10000가 됨.
*/

#include<stdio.h>

typedef struct app {
	int cost;
	int volume;
};
app apps[102];
int DT[101][10005];
int min = 2000000000;

int n, m;

int main() {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) scanf("%d", &(apps + i)->volume);
	for (int i = 1; i <= n; i++) scanf("%d", &(apps + i)->cost);

	for (int i = 0; i <= 100; i++) {
		for (int q = 0; q <= 10001; q++) 
			DT[i][q] = -1;
	}
	DT[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		app current = apps[i];
		int curr = i - 1;

		for (int q = 0; q <= 10000; q++) {
			if (DT[curr][q] != -1) {
				if (DT[i][q] == -1 || DT[i][q] < DT[curr][q]) DT[i][q] = DT[curr][q];
				if (DT[i][q + current.cost] == -1 || DT[i][q + current.cost] < DT[curr][q] + current.volume)
					DT[i][q + current.cost] = DT[curr][q] + current.volume;
			}

			if (DT[i][q] != -1 && DT[i][q] >= m && q < min) min = q;
		}

		
	}

	printf("%d", min);
}