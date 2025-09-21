#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1987_���ĺ� ----

	��Ʈ��ŷ�� ����Ѵ�.
	���⼭ visited�� �ƴ�, ���ĺ� ����� ���� ������ ���� ���Ѵ�.
	level�� ���� Ŭ ����, max���� �����ذ���.

*/


#include<stdio.h>

bool alphabet[30];

char map[25][25];
int n, m;

int MAX = 0;

void backTracking(int x, int y, int level) {
	char curr = map[x][y];
	if (level > MAX) MAX = level;
	alphabet[curr - 'A'] = true;

	if (x > 1 && alphabet[map[x - 1][y] - 'A'] == 0) backTracking(x - 1, y, level + 1);
	if (y > 1 && alphabet[map[x][y - 1] - 'A'] == 0) backTracking(x, y - 1, level + 1);
	if (x < n && alphabet[map[x + 1][y] - 'A'] == 0) backTracking(x + 1, y, level + 1);
	if (y < m && alphabet[map[x][y + 1] - 'A'] == 0) backTracking(x, y + 1, level + 1);


	alphabet[curr - 'A'] = false;
}


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf(" %c", &map[i][q]);
		}
	}

	backTracking(1, 1, 1);

	printf("%d", MAX);
}