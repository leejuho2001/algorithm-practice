/*
	---- 14940_���� �ִܰŸ� ----

	���̵��:

	2�� ����� ���� ���� ������ BFS Ž���� ����Ѵ�.
	�� ĭ���� ����ġ�� �ٸ��� �ʱ� ������, visited ���θ� �����ָ� �ȴ�.
	��� visited �׸��� -1(���� �� ����)���� ǥ�����ְ�, BFS�� �����ϸ鼭 �����Ѵ�.

	*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

int initialX;
int initialY;

queue<int>xQueue;
queue<int>yQueue;

int map[1050][1050];
int visited[1050][1050];

int n, m;

void visitedInitialize() {
	for (int x = 0; x < n; x++) 
		for (int y = 0; y < m; y++) visited[x][y] = -1;
	// visited�� ��� ��ǥ�� -1(�Ȱ���)���� �ʱ�ȭ
}

void input() {
	scanf("%d%d", &n, &m);
	visitedInitialize();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			scanf("%d", &map[x][y]);
			if (map[x][y] == 0) visited[x][y] = 0;  
			//�� �� ���� ���̶�� visited������ �� �� ���� ���̶�� ǥ��

			if (map[x][y] == 2) {
				initialX = x;
				initialY = y;
			}
			// ���������̶�� �ش� ������ �������� ���� ǥ��
		}
	}

}

void pushCoord(int x, int y, int value) {
	visited[x][y] = value;
	
	xQueue.push(x);
	yQueue.push(y);
}

void BFS(int initialDist) {
	pushCoord(initialX, initialY, initialDist);

	while (!xQueue.empty()) {
		
		int x = xQueue.front();
		int y = yQueue.front();
		xQueue.pop();
		yQueue.pop();

		if (x > 0 && map[x - 1][y] != 0 && visited[x - 1][y] == -1)
			pushCoord(x - 1, y, visited[x][y] + 1);

		if (y > 0 && map[x][y-1] != 0 && visited[x][y - 1] == -1)
			pushCoord(x, y-1, visited[x][y] + 1);

		if (x < n - 1 && map[x + 1][y] != 0 && visited[x + 1][y] == -1)
			pushCoord(x + 1, y, visited[x][y] + 1);

		if (y < m - 1 && map[x][y + 1] != 0 && visited[x][y + 1] == -1)
			pushCoord(x, y + 1, visited[x][y] + 1);
	}
}

void output() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			printf("%d ", visited[x][y]);
		}
		printf("\n");
	}
}


int main() {
	input();
	BFS(0);
	output();
}

	