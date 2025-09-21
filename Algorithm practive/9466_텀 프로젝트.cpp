#define _CRT_SECURE_NO_WARNINGS
/*
	9466_ 텀 프로젝트
	메인아이디어 1. 단순 구현으로 구한다.

	1. 하나의 사이클이 완성될 경우, 그 외부에서 해당 사이클로 들어가는 경우 자기 자신으로 돌아올 수 없음.
	따라서, 사이클이 생기면 사이클을 표시해줌.

	2. 따라서 세가지 경우로 나뉨
	1. 탐색을 한 번 함.
	2. 탐색을 한 뒤, 사이클에 존재하는 것으로 판단됨
	3. 탐색을 하지 않음.

	3번 경우일 경우 해당 위치를 시작으로 탐색을 시작함.

	그리고 3번 경우가 없어졌을 때 1번 경우가 팀에 속하지 못한 경우에 해당한다.

	** 모든 학생 수를 시작으로 사이클에 속하는 걸 발견할 때 마다 -1을 해감.
	
	여기에서 구분해야 하는 것은
	이전에 탐색한 것인가, 이번에 탐색한 것인가? 하는 것인데,
	이를 위해서 위의 1, 2, 3 case들을 '나머지' 로 구분한다.
	3가지 경우이므로 i번째 탐색일 경우, 1을 3i+1, 2를 3i+2로 표현한다.
	탐색을 하지 않은경우는 0으로 유지된다.
*/

#include<stdio.h>

int testCase;
int n, cnt;
int students[100005];
int selects[100005];

void init() {
	cnt = n;
	for (int i = 1; i <= n; i++) students[i] = 0;
}

void checker(int start, int lev) {
	int current = start;
	
	while (students[current] == 0) {
		students[current] = lev * 3 + 1;
		current = selects[current];
	}

	if (students[current] == lev * 3 + 1) {
		while (students[current] == lev * 3 + 1) {
			students[current] = start * 3 + 2;
			current = selects[current];
			cnt--;
		}
	}
	
}


int main() {
	scanf("%d", &testCase);
	for (int i = 0; i < testCase; i++) {
		scanf("%d", &n);
		init();
		int lev = 0;
		for (int q = 1; q <= n; q++) scanf("%d", selects + q);
		for (int q = 1; q <= n; q++) {
			if (students[q] == 0) {
				checker(q, lev); lev++;
			}
		}
		/*
		puts("");
		for (int q = 1; q <= n; q++) {
			printf("%d ", selects[q]);
		}
		puts("");
		for (int q = 1; q <= n; q++) {
			printf("%d ", students[q]);
		}
		puts("\n");
		// for debug
		*/
		printf("%d\n", cnt);
		
	}
}