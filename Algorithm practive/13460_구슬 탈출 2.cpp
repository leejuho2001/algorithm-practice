#define _CRT_SECURE_NO_WARNINGS

/*
	---- 12100_easy2048 ----

	10번까지 움직일 수 있음 -> 방향 : 4가지, 10번 움직임 가능
	탐색 가짓수 = 4^10 = 약 100만회.

	따라서, 백트래킹을 사용할 수 있음.

	굴리기 구현 방법
	굴리려는 방향으로 위치를 1씩 옮김. 굴리려는 방향 1칸 옆이 벽 / 구멍이 아닐때까지 반복.
	빨간 구슬/ 파란구슬 / 빨간구슬로 진행.

	빨간구슬과 파란구슬의 위치를 매개변수로 재귀를 하며 DFS를 하면 됨.
	종료조건 :	파란구슬이 O와 닿았을 경우 or level이 10을 넘어갈경우 -1 반환
				파란구슬이 0과 닿지 않고 빨간구슬이 0과 닿았을 경우 

	좌 / 우 / 상 / 하 
	방향으로 옴직이는 방식은
	x + wx, y + wy
	(여기서 wx는 x방향 가중치(기울기), wy는 y방향 가중치(기울기)) 를 나타내도록 하고,
	wx와 wy의 값을 바꿔가는 것으로 구현함.
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