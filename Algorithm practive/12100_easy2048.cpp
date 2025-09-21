#define _CRT_SECURE_NO_WARNINGS
/*
	---- 12100_easy2048 ----

	5번까지 움직일 수 있음 -> 방향 : 4가지, 5번 움직임 가능
	탐색 가짓수 = 4^5 = 1024회.

	따라서, 백트래킹을 사용할 수 있음.

	swipe 구현 방법
	오른쪽으로 swipe하는 경우, 오른쪽 원소부터 하나씩 검사해감.
	index = 끝 위치, temp : 0으로 초기화.

	temp가 0이 아닌 경우 : 같은게 들어오면 index위치에 더해줌, 그리고 index를 0으로 초기화
	다른게 들어오면 index++한 뒤, 그 위치로 index로 넣어줌.
*/


#include<stdio.h>
#include<stdlib.h>

typedef struct _board {
	int plate[22][22];
}board;

// inform 저장을 위한 plate
int maxx = 2;
int n;

void vertical(board* origin, board* newone, int mode) {
	int index;
	int value;
	int consts[2][3] = { {1, n, 1}, {n, 1, -1} };
	int startP = consts[mode][0], endP = consts[mode][1], weight = consts[mode][2];

	for (int i = 1; i <= n; i++) {
		index = startP;
		for (int q = startP; mode == 0 ? q <= endP : q >= endP; q += weight) {
			value = origin->plate[q][i];
			if (value != 0) {
				if (newone->plate[index][i] == 0) newone->plate[index][i] += value;
				else {
					if (newone->plate[index][i] == value) {
						newone->plate[index][i] += value;
						index += weight;
					}
					else {
						index += weight;
						newone->plate[index][i] += value;
					}
				}
			}
		}
	}
}

void horizontal(board* origin, board* newone, int mode) {
	int index;
	int value;
	int consts[2][3] = { {1, n, 1}, {n, 1, -1} };
	int startP = consts[mode][0], endP = consts[mode][1], weight = consts[mode][2];
	
	for (int i = 1; i <= n; i++) {
		index = startP;
		for (int q = startP; mode == 0? q<=endP : q>=endP; q += weight) {
			value = origin->plate[i][q];
			if (value != 0) {
				if (newone->plate[i][index] == 0) newone->plate[i][index] += value;
				else{
					if (newone->plate[i][index] == value) {
						newone->plate[i][index] += value;
						index += weight;
					}
					else {
						index += weight;
						newone->plate[i][index] += value;
					}
				}
			}
		}
	}
}

void RS(board* origin, board* newone) {
	horizontal(origin, newone, 1);
}

void LS(board* origin, board* newone) {
	horizontal(origin, newone, 0);
}

void DS(board* origin, board* newone) {
	vertical(origin, newone, 1);
}

void US(board* origin, board* newone) {
	vertical(origin, newone, 0);
}

void DFS(board* brd, int level) {
	if (level == 5) {
		for (int i = 1; i <= n; i++) {
			for (int q = 1; q <= n; q++) {
				if (maxx < brd->plate[i][q])
					maxx = brd->plate[i][q];
			}
		}
		return;
	}

	//r
	board* newR = (board*)malloc(sizeof(board)); *newR = {};
	RS(brd, newR);
	DFS(newR, level + 1);
	free(newR);
	//l
	board* newL = (board*)malloc(sizeof(board)); *newL = {};
	LS(brd, newL);
	DFS(newL, level + 1);
	free(newL);
	//u
	board* newU = (board*)malloc(sizeof(board)); *newU = {};
	US(brd, newU);
	DFS(newU, level + 1);
	free(newU);
	//d
	board* newD = (board*)malloc(sizeof(board)); *newD = {};
	DS(brd, newD);
	DFS(newD, level + 1);
	free(newD);

}


int main() {
	scanf("%d", &n);

	board* b = (board*) malloc(sizeof(board));
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf("%d", &b->plate[i][q]);
		}
	}

	
	DFS(b, 0);
	printf("%d", maxx);
	
	/*
	board* neww = (board*)malloc(sizeof(board));
	*neww = {};
	DS(b, neww);

	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			printf("%d ", neww->plate[i][q]);
		}
		puts("");
	}
	*/
	//for debug
	
}
