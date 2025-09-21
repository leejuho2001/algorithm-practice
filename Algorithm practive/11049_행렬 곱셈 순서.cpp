#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11049_행렬 곱셈 순서----

	::DP를 사용함.
	DP[i][q] : i번째 행렬부터 q번째 행렬까지의 행렬곱 중 최소를 반환
	따라서 DP[i][i] = 0
	DP[i][i+1]은 값이 바로 정해짐.

	길이를 1씩 늘려나가면서 가능한 분기점들을 모두 체크, min값을 체크함.
*/
#define uBound 2147483647;
#include<stdio.h>


typedef struct matrixSize {
	int row;
	int column;
}matSiz;
int DT[505][505];
matSiz sizes[505];

int get_cnt(int s, int m, int e) {
	return sizes[s].row * sizes[m].column * sizes[e].column;
}

int main() {
	int n; scanf("%d", &n);
	int MAX = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &sizes[i].row, &sizes[i].column);
		if (i > 1)
			DT[i - 1][i] = get_cnt(i - 1, i - 1, i);
	}

	for (int i = 2; i < n; i++) {
		for (int q = 1; q <= n - i; q++) {
			MAX = uBound;
			//DT[q][q+i] 에 대해 다룸.
			for (int z = 0; z < i; z++) {
				int curr = DT[q][q + z] + DT[q + z + 1][q + i] + get_cnt(q, q + z, q + i);
				
				if (curr < MAX) MAX = curr;
			}
			DT[q][q + i] = MAX;
		}
	}

	printf("%d", DT[1][n]);
}