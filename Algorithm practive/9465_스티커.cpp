#define _CRT_SECURE_NO_WARNINGS

/*
	---- 9465_스티커 ----

	아이디어 : 2*n 크기의 array에 대한 탐색
	
	n번째 위치 k의 스티커를 뜯는다고 가정했을때 가능한 경우 : 2가지
	
	n-1번째, k와 반대 위치
	n-2번째, k와 반대 위치
	
	-> n-2번째 k위치까지의 최대 + n-1번째, k와 반대 위치 = n-1번째, k와 반대 위치까지의 최대이기때문.

	해당 두가지 경우를 비교하여 값을 정하면 됨 : greedy를 사용할 수 있음.
	*/

#include<stdio.h>

int n;
int sticker[100050][2];
int results[100050][2];

int max(int a, int b) {
	return a > b ? a : b;
}


void greedy() {
	for (int i = 0; i <= n; i++) {
		if (i == 0) {
			results[i][0] = 0;
			results[i][1] = 0;
			continue;
		}

		if (i == 1) {
			results[i][0] = sticker[i][0];
			results[i][1] = sticker[i][1];
			continue;
		}

		results[i][0] = max(results[i - 1][1], results[i - 2][1]) + sticker[i][0];
		results[i][1] = max(results[i - 1][0], results[i - 2][0]) + sticker[i][1];
	}
}

int main() {
	int nn; scanf("%d", &nn);
	for (int _ = 0; _ < nn; _++) {
		scanf("%d", &n);

		for (int i = 0; i < 2; i++) {
			for (int k = 1; k <= n; k++) scanf("%d", &sticker[k][i]);
		}

		greedy();

		printf("%d", max(results[n][0], results[n][1]));
	}
}