#define _CRT_SECURE_NO_WARNINGS

/*
	---- 13549_숨바꼭질 3 ----

	아이디어:
	0. DFS를 사용하여 탐색한다. 
	1. 수빈이와 동생의 거리를 최소의 로 두고 진행한다.
	2. x+1로 가면 x-1로, x-1로 가면 x+1로 가지 못하도록 유형을 나누고 다음 탐색에 유형에 대한 정보를 전달한다.
	3. 탐색횟수가 최대횟수를 넘어가거나, 동생에게 도달하면 탐색을 중단한다.
	4. 수빈이 위치가 동생보다 클 경우, 무조건 x-1만 탐색한다

*/


#include<stdio.h>


int N, K;
int min = 12345678;
int minarr[10000000];

/*
	---- DFS ----
	:: param ::
	_level : 현재까지 수빈이가 이동한 횟수(탐색의 깊이)
	_n : 수빈의 위치
	_k : 동생의 위치
	type : 현재 탐색의 유형


	유형의 종류
	1: 이전 탐색에서 x+1로 이동함.
	-1: 이전 탐색에서 x-1로 이동함
	0: 이전 탐색에서 x*2로 이동함 or 초기상태

	x+1로 갈 조건
	n이 k보다 작을것.

	x-1로 갈 조건
	: n이 0보다 클것.
	n이 2*k를 넘어가지 말것.

	2로 갈 조건
	: n이 0보다 크고 k보다 작을것.

	종료조건
	level이 minarr에 저장된 값보다 크거나 같을경우
	해당 지점에 도달했을경우 :: min값을 다시 초기화.


	*/

void DFS(int _level, int _n, int _k, int _type) {
	int n = _n;
	int k = _k;
	int level = _level;
	int type = _type;
	//printf("%d %d %d\n", level, n, k);

	if (level < minarr[n]) minarr[n] = level;
	if (level>minarr[n]) return;

	if (n == k) {
		return;
	}

	if (n < k) DFS(level + 0, n * 2, k, 0);

	if (n < k && _type >= 0) {
		DFS(level + 1, n + 1, k, 1);
	}

	if (n>k/2 && n<3*k/2 && _type <= 0) {
		DFS(level + 1, n - 1, k, -1);
	}

}

void init() {
	for (int i = 0; i < K + 10; i++) {
		minarr[i] = 12345678;
	}
}


int main() {
	scanf("%d %d", &N, &K);
	init();
	DFS(0, N, K, 0);

	printf("%d", minarr[K]);
}
