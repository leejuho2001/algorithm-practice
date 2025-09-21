#define _CRT_SECURE_NO_WARNINGS

/*
	---- 13549_숨바꼭질 3 ----

	아이디어:
	0. BFS를 사용하여 탐색한다.
	1. BFS를 사용하면서 DT에 저장된 값과 비교하며 진행한다.
	2. 0의 범위를 정한다. n이 3/2k 보다 크면 안되고, n이 0보다 작아선 안된다.

*/

#include<stdio.h>
#include<queue>
using namespace std;

queue<int>forBFS;
int DT[200050];
int N, K;

void BFS(int _startValue) {
	DT[K] = 12345679;
	DT[N] = 0;
	forBFS.push(_startValue);

	while (!forBFS.empty()) {
		
		
		int current = forBFS.front();
		if (DT[current] > DT[K])break;
		//printf("%d - %d", current, DT[current]);

		if (current < K && current * 2 < K * 3 / 2) {
			if (DT[current * 2] > DT[current]) {
				DT[current * 2] = DT[current];
				forBFS.push(current * 2);
				//printf("  goto  %d", current * 2);
			}
		}

		if (current < K) {
			if (DT[current + 1] > DT[current] + 1) {
				
				DT[current + 1] = DT[current] + 1;

				//printf("   %d %d", DT[current + 1], DT[current]);
				forBFS.push(current + 1);
				//printf("  goto  %d", current + 1);
			}
		}

		if (current > 0) {
			if (DT[current - 1] > DT[current] + 1) {
				DT[current - 1] = DT[current] + 1;
				forBFS.push(current - 1);
				//printf("  goto  %d", current - 1);
			}
		}

		//puts("");
		forBFS.pop();
	}
}

// init :: 최소를 구하는 항목히므로, max값을 임의로 대입하여 초기화시켜줌.
void init() {
	for (int i = 0; i < 200000; i++) DT[i] = 12345678;
}

int main() {
	
	init();
	scanf("%d %d", &N, &K);
	
	BFS(N);
	printf("%d", DT[K]);
}

