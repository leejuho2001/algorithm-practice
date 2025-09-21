/*
	---- 14940_쉬운 최단거리 ----

	아이디어:

	2로 저장된 곳이 시작 지점인 BFS 탐색을 사용한다.
	각 칸마다 가중치가 다르지 않기 때문에, visited 여부만 따져주면 된다.
	모든 visited 항목은 -1(가본 적 없음)으로 표시해주고, BFS를 진행하면서 갱신한다.

	*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

int initialX;
int initialY;

queue<int>xQueue;
queue<int>yQueue;

int map[1050][1050];
int visited[1050][1050];

int n, m;

void visitedInitialize() {
	for (int x = 0; x < n; x++) 
		for (int y = 0; y < m; y++) visited[x][y] = -1;
	// visited의 모든 좌표를 -1(안가봄)으로 초기화
}

void input() {
	scanf("%d%d", &n, &m);
	visitedInitialize();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			scanf("%d", &map[x][y]);
			if (map[x][y] == 0) visited[x][y] = 0;  
			//갈 수 없는 벽이라면 visited에서도 갈 수 없는 벽이라고 표시

			if (map[x][y] == 2) {
				initialX = x;
				initialY = y;
			}
			// 시작지점이라면 해당 변수의 시작지점 값을 표시
		}
	}

}

void pushCoord(int x, int y, int value) {
	visited[x][y] = value;
	
	xQueue.push(x);
	yQueue.push(y);
}

void BFS(int initialDist) {
	pushCoord(initialX, initialY, initialDist);

	while (!xQueue.empty()) {
		
		int x = xQueue.front();
		int y = yQueue.front();
		xQueue.pop();
		yQueue.pop();

		if (x > 0 && map[x - 1][y] != 0 && visited[x - 1][y] == -1)
			pushCoord(x - 1, y, visited[x][y] + 1);

		if (y > 0 && map[x][y-1] != 0 && visited[x][y - 1] == -1)
			pushCoord(x, y-1, visited[x][y] + 1);

		if (x < n - 1 && map[x + 1][y] != 0 && visited[x + 1][y] == -1)
			pushCoord(x + 1, y, visited[x][y] + 1);

		if (y < m - 1 && map[x][y + 1] != 0 && visited[x][y + 1] == -1)
			pushCoord(x, y + 1, visited[x][y] + 1);
	}
}

void output() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			printf("%d ", visited[x][y]);
		}
		printf("\n");
	}
}


int main() {
	input();
	BFS(0);
	output();
}

	