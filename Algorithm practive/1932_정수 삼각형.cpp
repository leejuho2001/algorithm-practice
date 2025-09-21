#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1932_정수 삼각형 ----

	아이디어 : 맨 밑층부터 더 큰걸 올려가면서 구한다.
	n이 있을 때, 수의 최대 갯수는 n^2/2, 핵심 연산인 비교연산은 단 한번 들어간다.
	따라서 시간복잡도는 O(n^2).

	1. 맨 아래 - 1 층부터 시작함.
	n번째 원소는 n, n+1번 DT + 해당 DT에 해당하는 삼각형의 원소값의 합을 비교하여 올림.
	1층까지 반복
*/



#include<stdio.h>

int triangle[550][550]; // 원소 저장용
int DT[550][550];		// DP를 위한 테이블

int n;

//더 큰 밸류를 반환함
int biggerValue(int _valA, int _valB) {
	return _valA > _valB ? _valA : _valB;
}

//다이나믹 프로그래밍
int DP() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			DT[i][j] = biggerValue(DT[i + 1][j] + triangle[i + 1][j], DT[i + 1][j + 1] + triangle[i + 1][j + 1]);
		}
	}

	return DT[0][0];
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) scanf("%d", &triangle[i][j]);
	}

	DP();
	printf("%d", DP()+triangle[0][0]);
}