#define _CRT_SECURE_NO_WARNINGS
/*
	---- 12100_easy2048 ----

	5������ ������ �� ���� -> ���� : 4����, 5�� ������ ����
	Ž�� ������ = 4^5 = 1024ȸ.

	����, ��Ʈ��ŷ�� ����� �� ����.

	swipe ���� ���
	���������� swipe�ϴ� ���, ������ ���Һ��� �ϳ��� �˻��ذ�.
	index = �� ��ġ, temp : 0���� �ʱ�ȭ.

	temp�� 0�� �ƴ� ��� : ������ ������ index��ġ�� ������, �׸��� index�� 0���� �ʱ�ȭ
	�ٸ��� ������ index++�� ��, �� ��ġ�� index�� �־���.
*/


#include<stdio.h>
#include<stdlib.h>

typedef struct _board {
	int plate[22][22];
}board;

// inform ������ ���� plate
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
