#define _CRT_SECURE_NO_WARNINGS
/*
	---- 9252_LCS2 ----

	LCS와 달라진 점 : 최장길이 공통 문자열을 출력해줘야함

	해결방식 : DT외에도 BEFORE 를 만들어, 해당 공간에 이전 LCS의 끝 탐색의 위치를 저장함.
	ACAYKP
	CAPCAK 일때, 
	BEFORE[5][5][0] = 4,
	BEFORE[5][5][1] = 5

	이걸 통해 재귀로 역추적함.
*/
#include<stdio.h>
#include<string.h>

char strA[1005];
char strB[1005];

int DT[1005][1005];
int BEFORE[1005][1005][2];

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
	int case2 = LCS(n, m - 1);
	int case3 = LCS(n - 1, m - 1) + b;
	DT[n][m] = max(case1, case2, case3);

	if (DT[n][m] == case1) {
		BEFORE[n][m][0] = n - 1, BEFORE[n][m][1] = m;
	}
	if (DT[n][m] == case2) {
		BEFORE[n][m][0] = n, BEFORE[n][m][1] = m - 1;
	}
	if (DT[n][m] == case3) {
		BEFORE[n][m][0] = n - 1, BEFORE[n][m][1] = m - 1;
	}

	return DT[n][m];
}

void reverse_track(int n, int m) {
	if (n < 0 || m < 0) return;

	if (n == 0 && m == 0) {
		if (strA[n] == strB[m]) printf("%c", strA[n]);
		return;
	}

	reverse_track(BEFORE[n][m][0], BEFORE[n][m][1]);
	if (strA[n] == strB[m]) printf("%c", strA[n]);
}

int main() {
	scanf("%s", strA);
	scanf("%s", strB);
	init();
	int res = LCS(strlen(strA) - 1, strlen(strB) - 1);
	printf("%d", res);
	if (res != 0) { 
		puts("");
		reverse_track(strlen(strA) - 1, strlen(strB) - 1); 
	}
}