#define _CRT_SECURE_NO_WARNINGS

/*
	---- 13549_���ٲ��� 3 ----

	���̵��:
	0. BFS�� ����Ͽ� Ž���Ѵ�.
	1. BFS�� ����ϸ鼭 DT�� ����� ���� ���ϸ� �����Ѵ�.
	2. 0�� ������ ���Ѵ�. n�� 3/2k ���� ũ�� �ȵǰ�, n�� 0���� �۾Ƽ� �ȵȴ�.

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

// init :: �ּҸ� ���ϴ� �׸����Ƿ�, max���� ���Ƿ� �����Ͽ� �ʱ�ȭ������.
void init() {
	for (int i = 0; i < 200000; i++) DT[i] = 12345678;
}

int main() {
	
	init();
	scanf("%d %d", &N, &K);
	
	BFS(N);
	printf("%d", DT[K]);
}

