#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1799_비숍 ----

	대각선 기준으로, 룩에 대한 문제라고 할 수 있음.
	따라서 대각선을 기준으로 탐색을 시작함

	아래로 한 칸씩 내려가면서 겹치지 않는 곳에 놓아보면서 백트래킹을 사용.

	일반적인 백트래킹 = 시간초과 발생함

	따라서, Branch 연산을 해주어야 할 필요가 있음.
	level 하나당 1 개의 비숍만 놓을 수 있다는 것을 이용,
	남은 level을 모두 더해도 MAXX와 작거나 같다면 그 탐색을 하지 않도록 한다.
	(31번 구현 줄)
*/
#include<stdio.h>

int n;
int visited[25] = {};
int map[15][15] = {};
int MAXX = 0;

int get_dtNum(int x, int y) {
	return x - y + n;
}

void search(int level, int cnt) {
	int initX, initY;

	if (cnt + 2 * n - level < MAXX) return;

	if (level > n * 2) {
		if (cnt > MAXX) MAXX = cnt;
		return;
	}

	if (level > n + 1) {
		initX = n;
		initY = level - n;
	}
	else {
		initX = level-1;
		initY = 1;
	}

	int x = initX, y = initY;
	while ( x > 0 && y <= n) {
		if (map[x][y] == 1 && visited[get_dtNum(x, y)] == false) {
			visited[get_dtNum(x, y)] = true;
			search(level + 1, cnt + 1);
			visited[get_dtNum(x, y)] = false;
		}
		x--;
		y++;
	}

	search(level + 1, cnt); // 해당 대각선에 비숍을 안 깐 경우.
}



void initInput() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf("%d", &map[i][q]);
		}
	}
}

int main() {
	initInput();
	search(2, 0);

	printf("%d", MAXX);
}