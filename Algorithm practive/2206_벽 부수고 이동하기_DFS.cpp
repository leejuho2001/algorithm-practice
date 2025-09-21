#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2206_�� �μ��� �̵��ϱ� ----
	���̵�� : 1�������� ���� �μ� �� �ִ�.
	���� �ν��°��� ���� ���θ� ����� DFS�� �����Ѵ�.

	��͸� ���� DFS��, param���� ���� �ν��°� ���θ� �Է��ϴ� ������� �ذ� ����

	--> �ð��ʰ� 
*/


#include<stdio.h>
using namespace std;

int n, m;
int map[1050][1050];
int DT[1050][1050];

/*
	---- DFS ----
	:: param ::
	int		x, y	: ���� ��ǥ�� x���� y�� ����
	int		depth	: ���ݱ��� �� �Ÿ��� ����
	bool	broken	: ���ݱ��� ���鼭 1�� �̻� ���� �ν����� ���θ� ����

	:: action ::
	1x1���� �����ؼ� nxm���� ������ dfs�� ���� 
	��ǥ�� ��ġ�� broken���� ���� ���� �ִ� �κп� ���� �ൿ���ɿ��θ� �����Ѵ�.
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
	DT[1][1] = 1;
	DFS(1, 1, 1, 0);

	if (DT[n][m] == 0) printf("-1");
	else printf("%d", DT[n][m]);
}