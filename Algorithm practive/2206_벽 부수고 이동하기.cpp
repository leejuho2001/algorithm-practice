#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_벽 부수고 이동하기 ----
	아이디어 : 1번까지만 벽을 부술 수 있다.
	벽을 부쉈는가에 대한 여부를 나누어서 BFS를 진행한다.
	따라서 DT는 x, y좌표, 벽 부숨 여부를 저장한다.

	--> 메모리 초과
	: 모든 칸을 나타낸 DT가 문제일 것으로 추정함.
*/


#include<stdio.h>
#include<queue>
using namespace std;

typedef struct breakCoord {
	int x;
	int y;
	int broken;
}brCoord;

int map[1050][1050];
int DT[1050][1050][2];
queue<brCoord> forBFS;

int n, m;

void searching(int x1, int y1, int x2, int y2, int broken) {

	if (map[x2][y2] == 1) {
		if (broken == 1) return;
		else {
			if (DT[x2][y2][1] == 0) {
				DT[x2][y2][1] = DT[x1][y1][0] + 1;

				forBFS.push({ x2, y2, 1 });
			}
		}
	}

	if (map[x2][y2] == 0) {
		if (broken == 1) {
			if (DT[x2][y2][1] == 0) {
				DT[x2][y2][1] = DT[x1][y1][1] + 1;
				forBFS.push({ x2, y2, 1 });
			}
		}
		else {
			if (DT[x2][y2][0] == 0) {
				DT[x2][y2][1] = DT[x1][y1][1] + 1;
				forBFS.push({ x2, y2, 0 });
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

	forBFS.push({ 1, 1, 0 });
	DT[1][1][0] = 1;
	DT[1][1][1] = 999;

	while (!forBFS.empty()) {
		brCoord current = forBFS.front();
		int x = current.x, y = current.y;

		if (x == n && y == m) return DT[x][y][current.broken];
		
		if (x > 1) {
			searching(x, y, x - 1, y, current.broken);
		}

		if (y > 1) {
			searching(x, y, x, y - 1, current.broken);
		}

		if (x < n) {
			searching(x, y, x + 1, y, current.broken);
		}

		if (y < m) {
			searching(x, y, x, y + 1, current.broken);
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
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			char temp;  scanf(" %c", &temp);
			map[i][q] = temp - '0';
		}
	}
}


int main() {
	scanf("%d %d", &n, &m);
	map_input();
	int result = BFS();
	printf("%d", result);

}