#define _CRT_SECURE_NO_WARNINGS

/*
	---- 5719_���� �ִ� ��� ----

	basic : bfs�� ���� 1ȸ Ž��
	���⼭ visited�� �ּҰŸ� + ���� ����� ��ȣ�� ������.

	���� ��� ���� ������ ���� �������ذ��� �ִܰ���� ���ε��� ���̸� 0(����ȵ�) ���� ����.
	-> �ٽ� bfs�� ���� Ž��. ���⼭ �ϳ� �̻��� �߰� ������ ��

	�������� �߰� ���� : before node == -1 << �̷��ٸ� ������ ���� �������� �ʴ°�.,
	����, �ش� ������ or�������� �߰�����.

	������, before�� �ƿ� �������� �ʴ� ����� �� ����.
	�̸� ���ؼ� before != -1���� ���� �������־����.
*/

#include<stdio.h>
#include<queue>
using namespace std;
queue<int> forBFS;
int map[505][505];
int visited[505];
int before[505];

int s, d;
int n, m;
void init() {
	for (int i = 0; i <= 500; i++) {
		for (int q = 0; q <= 500; q++) {
			map[i][q] = 0;
		}
		visited[i] = 0;
		before[i] = -1;
	}
}

void BFS() {
	forBFS.push(s);
	while (!forBFS.empty()) {
		int curr = forBFS.front();

		for(int i=0)
	}
}

int main() {
	while (1) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0) return 0;
		scanf("%d %d", &s, &d);
		int a, b, c;
		for (int _ = 0; _ < m; _++) {
			scanf("%d %d %d", &a, &b, &c);
			map[a][b] = c;
		}

	}
}