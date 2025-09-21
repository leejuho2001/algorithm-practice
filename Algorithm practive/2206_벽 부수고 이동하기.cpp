#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_�� �μ��� �̵��ϱ� ----
	���̵�� : 1�������� ���� �μ� �� �ִ�.
	���� �ν��°��� ���� ���θ� ����� BFS�� �����Ѵ�.
	���� DT�� x, y��ǥ, �� �μ� ���θ� �����Ѵ�.

	--> �޸� �ʰ�
	: ��� ĭ�� ��Ÿ�� DT�� ������ ������ ������.
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
	1,1 ���� �����ϴ� BFSŽ���� ������.
	�̵��� ��, �Ʒ�, ��, ��� ����
	Ž�� ���� : �ƿ� Ž���� ������� �ʾҰų�, ��������� �Ÿ� +1�� DT�� ����� ������ �������
	+ ���� �μ��� �ʾ��� ��� �׵θ��� �ƴ� ������ Ž�� ����

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
	nxm ũ���� �迭 map�� ���� ������ �ִ´�.
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