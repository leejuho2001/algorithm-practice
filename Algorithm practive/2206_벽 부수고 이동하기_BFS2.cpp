#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_�� �μ��� �̵��ϱ� bfs2 ----
	����BFS���� ������ :
	������ �Ÿ��� �����ϴ� DT�� ���� �����ϴ� map�� �ڷ����� 
	bool�� ��ȯ,

	���� broken ������ �߰��� ��� boCoord�� ��������� �Ÿ��� �߰�.
	===> �޸��� ��뷮 ����

	::: �ش� Ǯ�̸� ���� ���� ������ ����.
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
	1,1 ���� �����ϴ� BFSŽ���� ������.
	�̵��� ��, �Ʒ�, ��, ��� ����
	Ž�� ���� : �ƿ� Ž���� ������� �ʾҰų�, ��������� �Ÿ� +1�� DT�� ����� ������ �������
	+ ���� �μ��� �ʾ��� ��� �׵θ��� �ƴ� ������ Ž�� ����

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
	nxm ũ���� �迭 map�� ���� ������ �ִ´�.
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