#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_벽 부수고 이동하기 ----
	아이디어 : 1번까지만 벽을 부술 수 있다.
	벽을 부쉈는가에 대한 여부를 나누어서 DFS를 진행한다.

	재귀를 통한 DFS에, param으로 벽을 부쉈는가 여부를 입력하는 방식으로 해결 가능

	--> 시간초과 
*/


#include<stdio.h>
using namespace std;

int n, m;
int map[1050][1050];
int DT[1050][1050];

/*
	---- DFS ----
	:: param ::
	int		x, y	: 현재 좌표의 x값과 y값 저장
	int		depth	: 지금까지 온 거리를 저장
	bool	broken	: 지금까지 오면서 1번 이상 벽을 부쉈는지 여부를 저장

	:: action ::
	1x1에서 시작해서 nxm으로 끝나는 dfs를 시행 
	좌표의 위치와 broken값에 따라서 벽이 있는 부분에 대한 행동가능여부를 결정한다.
*/

void DFS(int x, int y, int depth, bool broken) {

	if (DT[n][m] != 0 && depth > DT[n][m]) return;

	if (broken == 1) {
		if (x > 1) {
			if (map[x - 1][y] == 1);
			else {
				if (DT[x - 1][y] == 0 || DT[x - 1][y] > depth + 1) {
					DT[x - 1][y] = depth + 1;
					DFS(x - 1, y, depth+1, 1);
				}
			}
		}

		if (x < n) {
			if (map[x + 1][y] == 1);
			else {
				if (DT[x + 1][y] == 0 || DT[x + 1][y] > depth + 1) {
					DT[x + 1][y] = depth + 1;
					DFS(x + 1, y, depth + 1, 1);
				}
			}
		}

		if (y > 1) {
			if (map[x][y - 1] == 1);
			else {
				if (DT[x][y - 1] == 0 || DT[x][y - 1] > depth + 1) {
					DT[x][y - 1] = depth + 1;
					DFS(x, y - 1, depth + 1, 1);
				}
			}
		}

		if (y < m) {
			if (map[x][y + 1] == 1);
			else {
				if (DT[x][y + 1] == 0 || DT[x][y + 1] > depth + 1) {
					DT[x][y + 1] = depth + 1;
					DFS(x, y + 1, depth + 1, 1);
				}
			}
		}
	}
	else {
		if (x > 1) {
			if (DT[x - 1][y] == 0 || DT[x - 1][y] > depth + 1) {
				DT[x - 1][y] = depth + 1;
				if (map[x + 1][y] == 1) DFS(x - 1, y, depth + 1, 1);
				else DFS(x - 1, y, depth + 1, 0);
			}
		}

		if (x < n) {
			if (DT[x + 1][y] == 0 || DT[x + 1][y] > depth + 1) {
				DT[x + 1][y] = depth + 1;
				if (map[x + 1][y] == 1) DFS(x + 1, y, depth + 1, 1);
				else DFS(x + 1, y, depth + 1, 0);
			}
		}

		if (y > 1) {
			if (DT[x][y - 1] == 0 || DT[x][y - 1] > depth + 1) {
				DT[x][y - 1] = depth + 1;
				if (map[x][y - 1] == 1) DFS(x, y - 1, depth + 1, 1);
				else DFS(x, y - 1, depth + 1, 0);
			}
		}

		if (y < m) {
			if (DT[x][y + 1] == 0|| DT[x][y + 1] > depth + 1) {
				DT[x][y + 1] = depth + 1;
				if (map[x][y + 1] == 1) DFS(x, y + 1, depth + 1, 1);
				else DFS(x, y + 1, depth + 1, 0);
			}
		}
	}

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
	DT[1][1] = 1;
	DFS(1, 1, 1, 0);

	if (DT[n][m] == 0) printf("-1");
	else printf("%d", DT[n][m]);
}