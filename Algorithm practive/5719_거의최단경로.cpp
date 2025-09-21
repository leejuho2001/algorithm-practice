#define _CRT_SECURE_NO_WARNINGS

/*
	---- 5719_거의 최단 경로 ----

	basic : bfs를 통해 1회 탐색
	여기서 visited에 최소거리 + 이전 노드의 번호를 저장함.

	이전 노드 저장 정보를 통해 역추적해가며 최단경로의 도로들의 길이를 0(연결안됨) 으로 수정.
	-> 다시 bfs를 통해 탐색. 여기서 하나 이상의 추가 조건을 줌

	구상중인 추가 조건 : before node == -1 << 이렇다면 어차피 길이 존재하지 않는것.,
	따라서, 해당 조건을 or연산으로 추가해줌.

	하지만, before이 아예 존재하지 않는 경우일 수 있음.
	이를 위해서 before != -1까지 같이 적용해주어야함.
*/

#include<stdio.h>
#include<queue>
using namespace std;
queue<int> forBFS;
int map[505][505];
int visited[505];
int before[505];

int s, d;
int n, m;
void init() {
	for (int i = 0; i <= 500; i++) {
		for (int q = 0; q <= 500; q++) {
			map[i][q] = 0;
		}
		visited[i] = 0;
		before[i] = -1;
	}
}

void BFS() {
	forBFS.push(s);
	while (!forBFS.empty()) {
		int curr = forBFS.front();

		for(int i=0)
	}
}

int main() {
	while (1) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0) return 0;
		scanf("%d %d", &s, &d);
		int a, b, c;
		for (int _ = 0; _ < m; _++) {
			scanf("%d %d %d", &a, &b, &c);
			map[a][b] = c;
		}

	}
}