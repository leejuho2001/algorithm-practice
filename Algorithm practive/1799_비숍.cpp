#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1799_��� ----

	�밢�� ��������, �迡 ���� ������� �� �� ����.
	���� �밢���� �������� Ž���� ������

	�Ʒ��� �� ĭ�� �������鼭 ��ġ�� �ʴ� ���� ���ƺ��鼭 ��Ʈ��ŷ�� ���.

	�Ϲ����� ��Ʈ��ŷ = �ð��ʰ� �߻���

	����, Branch ������ ���־�� �� �ʿ䰡 ����.
	level �ϳ��� 1 ���� ��� ���� �� �ִٴ� ���� �̿�,
	���� level�� ��� ���ص� MAXX�� �۰ų� ���ٸ� �� Ž���� ���� �ʵ��� �Ѵ�.
	(31�� ���� ��)
*/
#include<stdio.h>

int n;
int visited[25] = {};
int map[15][15] = {};
int MAXX = 0;

int get_dtNum(int x, int y) {
	return x - y + n;
}

void search(int level, int cnt) {
	int initX, initY;

	if (cnt + 2 * n - level < MAXX) return;

	if (level > n * 2) {
		if (cnt > MAXX) MAXX = cnt;
		return;
	}

	if (level > n + 1) {
		initX = n;
		initY = level - n;
	}
	else {
		initX = level-1;
		initY = 1;
	}

	int x = initX, y = initY;
	while ( x > 0 && y <= n) {
		if (map[x][y] == 1 && visited[get_dtNum(x, y)] == false) {
			visited[get_dtNum(x, y)] = true;
			search(level + 1, cnt + 1);
			visited[get_dtNum(x, y)] = false;
		}
		x--;
		y++;
	}

	search(level + 1, cnt); // �ش� �밢���� ����� �� �� ���.
}



void initInput() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf("%d", &map[i][q]);
		}
	}
}

int main() {
	initInput();
	search(2, 0);

	printf("%d", MAXX);
}