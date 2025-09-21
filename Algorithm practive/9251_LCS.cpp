#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

char strA[1005];
char strB[1005];

int DT[1005][1005];

void init() {
	for (int i = 0; i < 1005; i++) {
		for (int q = 0; q < 1004; q++) {
			DT[i][q] = -1;
		}
	}
}

int max(int a, int b, int c) {
	int temp = a > b ? a : b;
	int res = temp > c ? temp : c;

	return res;
}

int LCS(int n, int m) {
	if (n < 0 || m < 0) return 0;

	if (DT[n][m] >= 0) return DT[n][m];

	int b = strA[n] == strB[m] ? 1 : 0;

	int case1 = LCS(n - 1, m);
	int case2 = LCS(n , m - 1);
	int case3 = LCS(n - 1, m - 1) + b;

	return DT[n][m] = max(case1, case2, case3);
}

int main() {
	scanf("%s", strA);
	scanf("%s", strB);
	init();
	printf("%d", LCS(strlen(strA) - 1, strlen(strB) - 1));
}