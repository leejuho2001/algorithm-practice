#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_벽 부수고 이동하기 bfs2 ----
	기존BFS와의 변경점 :
	기존의 거리를 저장하던 DT와 벽을 저장하던 map의 자료형을 
	bool로 전환,

	또한 broken 정보를 추가로 담던 boCoord에 현재까지의 거리를 추가.
	===> 메모리의 사용량 감소

	::: 해당 풀이를 통해 정답 판정을 받음.
	*/


#include<stdio.h>
#include<queue>
using namespace std;

typedef struct breakCoord {
	int x;
	int y;
	int dist;
	bool broken;
}brCoord;

bool map[1050][1050];
bool DT[1050][1050][2];
queue<brCoord> forBFS;

int n, m;

void searching(int x2, int y2, int dist, bool broken) {

	if (map[x2][y2] == 1) {
		if (broken == true) return;
		else {
			if (DT[x2][y2][1] == false) {
				DT[x2][y2][1] = true;

				forBFS.push({ x2, y2, dist+1, true });
			}
		}
	}

	if (map[x2][y2] == 0) {
		if (broken == true) {
			if (DT[x2][y2][1] == false) {
				DT[x2][y2][1] = true;
				forBFS.push({ x2, y2, dist+1, true });
			}
		}
		else {
			if (DT[x2][y2][0] == false) {
				DT[x2][y2][0] = true;
				forBFS.push({ x2, y2, dist+1, false });
			}
		}

	}
}

/*
	---- BFS ----

	:: action ::
	1,1 에서 시작하는 BFS탐색을 시행함.
	이동은 위, 아래, 좌, 우로 진행
	탐색 기준 : 아예 탐색이 진행되지 않았거나, 현재까지의 거리 +1이 DT에 저장된 값보다 작을경우
	+ 벽을 부수지 않았을 경우 테두리가 아닌 벽에도 탐색 가능

	*/
int BFS() {

	forBFS.push({ 1, 1, 1, 0 });
	DT[1][1][0] = true;
	DT[1][1][1] = true;

	while (!forBFS.empty()) {
		brCoord current = forBFS.front();
		int x = current.x, y = current.y;
		int dist = current.dist, broken = current.broken;

		if (x == n && y == m) return dist;

		if (x > 1) {
			searching(x - 1, y, dist, broken);
		}

		if (y > 1) {
			searching(x, y - 1, dist, broken);
		}

		if (x < n) {
			searching(x + 1, y, dist, broken);
		}

		if (y < m) {
			searching(x, y + 1, dist, broken);
		}

		forBFS.pop();
	}

	return -1;
}

/*
	---- map_input ----

	:: action ::
	nxm 크기의 배열 map에 맵의 정보를 넣는다.
*/

void map_input() {
	char temp;
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf(" %c", &temp);
			if (temp == '1') map[i][q] = true;
			else map[i][q] = false;
		}
	}
}


int main() {
	scanf("%d %d", &n, &m);
	map_input();
	int result = BFS();
	printf("%d", result);

}