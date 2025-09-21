#define _CRT_SECURE_NO_WARNINGS

/*
	---- 12100_easy2048 ----

	10������ ������ �� ���� -> ���� : 4����, 10�� ������ ����
	Ž�� ������ = 4^10 = �� 100��ȸ.

	����, ��Ʈ��ŷ�� ����� �� ����.

	������ ���� ���
	�������� �������� ��ġ�� 1�� �ű�. �������� ���� 1ĭ ���� �� / ������ �ƴҶ����� �ݺ�.
	���� ����/ �Ķ����� / ���������� ����.

	���������� �Ķ������� ��ġ�� �Ű������� ��͸� �ϸ� DFS�� �ϸ� ��.
	�������� :	�Ķ������� O�� ����� ��� or level�� 10�� �Ѿ��� -1 ��ȯ
				�Ķ������� 0�� ���� �ʰ� ���������� 0�� ����� ��� 

	�� / �� / �� / �� 
	�������� �����̴� �����
	x + wx, y + wy
	(���⼭ wx�� x���� ����ġ(����), wy�� y���� ����ġ(����)) �� ��Ÿ������ �ϰ�,
	wx�� wy�� ���� �ٲ㰡�� ������ ������.
*/
#include<stdio.h>

char map_info[13][13];

int dfs(int rx, int ry, int bx, int by, int level) {
	//printf("%d %d %d %d\n", rx, ry, bx, by);

	if (level == 10) return -1;
	int MAX = -1;
	int trx = rx, t_ry = ry, tbx = bx, tby = by;
	bool flagR = false, flagB = false;
	int wx = 1, wy = 0;
	//right
	while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx+=wx, t_ry+=wy; 
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;
	while (map_info[tbx + wx][tby + wy] == '.' && (tbx + wx != trx || tby + wy != t_ry)) tbx += wx, tby += wy;
	if (map_info[tbx + wx][tby + wy] == 'O') tbx = 123, flagB = true;
	if(flagR == false) 
		while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;

	if (flagB == true);
	else if (flagR == true ) return level+1;
	else {
		int res = dfs(trx, t_ry, tbx, tby, level + 1);
		if (res != -1 && (MAX == -1 || res < MAX)) MAX = res;
	}
	//left
	trx = rx, t_ry = ry, tbx = bx, tby = by;
	flagR = false, flagB = false;
	wx = -1, wy = 0;
	while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;
	while (map_info[tbx + wx][tby + wy] == '.' && (tbx + wx != trx || tby + wy != t_ry)) tbx += wx, tby += wy;
	if (map_info[tbx + wx][tby + wy] == 'O') tbx = 123, flagB = true;
	if (flagR == false)
		while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;

	if (flagR == true && flagB == false) return level + 1;

	if (flagB == true);
	else if (flagR == true) return level + 1;
	else {
		int res = dfs(trx, t_ry, tbx, tby, level + 1);
		if (res != -1 && (MAX == -1 || res < MAX)) MAX = res;
	}
	//up
	trx = rx, t_ry = ry, tbx = bx, tby = by;
	flagR = false, flagB = false;
	wx = 0, wy = 1;
	while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;
	while (map_info[tbx + wx][tby + wy] == '.' && (tbx + wx != trx || tby + wy != t_ry)) tbx += wx, tby += wy;
	if (map_info[tbx + wx][tby + wy] == 'O') tbx = 123, flagB = true;
	if (flagR == false)
		while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;

	if (flagR == true && flagB == false) return level + 1;

	if (flagB == true);
	else if (flagR == true) return level + 1;
	else {
		int res = dfs(trx, t_ry, tbx, tby, level + 1);
		if (res != -1 && (MAX == -1 || res < MAX)) MAX = res;
	}
	//down
	trx = rx, t_ry = ry, tbx = bx, tby = by;
	flagR = false, flagB = false;
	wx = 0, wy = -1;
	while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;
	while (map_info[tbx + wx][tby + wy] == '.' && (tbx + wx != trx || tby + wy != t_ry)) tbx += wx, tby += wy;
	if (map_info[tbx + wx][tby + wy] == 'O') tbx = 123, flagB = true;
	if (flagR == false)
		while (map_info[trx + wx][t_ry + wy] == '.' && (trx + wx != tbx || t_ry + wy != tby)) trx += wx, t_ry += wy;
	if (map_info[trx + wx][t_ry + wy] == 'O') trx = 123, flagR = true;

	if (flagR == true && flagB == false) return level + 1;

	if (flagB == true);
	else if (flagR == true) return level + 1;
	else {
		int res = dfs(trx, t_ry, tbx, tby, level + 1);
		if (res != -1 && (MAX == -1 || res < MAX)) MAX = res;
	}

	return MAX;
}

int main() {
	int rx = 0, ry = 0, bx = 0, by = 0;
	int x, y;
	scanf("%d %d", &x, &y);
	for (int i = 1; i <= x; i++) {
		for (int q = 1; q <= y; q++) {
			scanf(" %c", &map_info[i][q]);
			if (map_info[i][q] == 'R') {
				map_info[i][q] = '.';
				rx = i; ry = q;
			}
			else if (map_info[i][q] == 'B') {
				map_info[i][q] = '.';
				bx = i; by = q;
			}
		}
	}

	printf("%d", dfs(rx, ry, bx, by, 0));
}