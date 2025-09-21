#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2638_치즈 ----

	상 하 좌 우로 탐색 방향이 4 개가 있는 DFS 문제.
	특히 단지수 문제와 비슷한 형태를 가짐.

	다음에 녹아내릴 블럭에 대해 좌표만 저장해둔 뒤, 나중에 적용.
	적용하는 과정에서 적용되는 좌표 주변에 0(공기가 통하지 않은 빈공간) 이 있을경우,
	DFS를 통해 모든 연결된 공간을 -1(공기가 있음)로 초기화.

	--> + 첫 외부를 DFS를 통해서 구분함.
*/

#include<stdio.h>
#include<queue>
using namespace std;

typedef struct _crd {
	int x;
	int y;
}crd;

queue<crd> changelist;

int map[105][105];
int n, m;

void DFS1(int x, int y) {
	map[x][y] = -1;

	if (x > 0 && map[x - 1][y] == 0) DFS1(x - 1, y);
	if (y > 0 && map[x][y - 1] == 0)DFS1(x, y - 1);
	if (x <= n && map[x + 1][y] == 0)DFS1(x + 1, y);
	if (y <= m && map[x][y + 1] == 0)DFS1(x, y + 1);
}

int remain, phase;

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf("%d", &map[i][q]);
		
			if (map[i][q] == 1) remain++;
		}
	}

	DFS1(0, 0);

	int cnt;
	while (remain > 0) {
		phase++;
		for (int i = 1; i <= n; i++) {
			for (int q = 1; q <= m; q++) {
				if (map[i][q] == 1) {
					cnt = 0;
					if (map[i - 1][q] == -1) cnt++;
					if (map[i + 1][q] == -1) cnt++;
					if (map[i][q - 1] == -1) cnt++;
					if (map[i][q + 1] == -1) cnt++;

					if (cnt >= 2) {
						changelist.push({ i, q });
						//printf("%d %d %d\n", phase, i, q);
					}
				}
			}
		}
		while (!changelist.empty()) {
			//printf("change %d\n", phase);
			crd curr = changelist.front();
			DFS1(curr.x, curr.y);
			changelist.pop();
			remain--;
		}
	}

	printf("%d", phase);

}