#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2638_ġ�� ----

	�� �� �� ��� Ž�� ������ 4 ���� �ִ� DFS ����.
	Ư�� ������ ������ ����� ���¸� ����.

	������ ��Ƴ��� ���� ���� ��ǥ�� �����ص� ��, ���߿� ����.
	�����ϴ� �������� ����Ǵ� ��ǥ �ֺ��� 0(���Ⱑ ������ ���� �����) �� �������,
	DFS�� ���� ��� ����� ������ -1(���Ⱑ ����)�� �ʱ�ȭ.

	--> + ù �ܺθ� DFS�� ���ؼ� ������.
*/

#include<stdio.h>
#include<queue>
using namespace std;

typedef struct _crd {
	int x;
	int y;
}crd;

queue<crd> changelist;

int map[105][105];
int n, m;

void DFS1(int x, int y) {
	map[x][y] = -1;

	if (x > 0 && map[x - 1][y] == 0) DFS1(x - 1, y);
	if (y > 0 && map[x][y - 1] == 0)DFS1(x, y - 1);
	if (x <= n && map[x + 1][y] == 0)DFS1(x + 1, y);
	if (y <= m && map[x][y + 1] == 0)DFS1(x, y + 1);
}

int remain, phase;

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf("%d", &map[i][q]);
		
			if (map[i][q] == 1) remain++;
		}
	}

	DFS1(0, 0);

	int cnt;
	while (remain > 0) {
		phase++;
		for (int i = 1; i <= n; i++) {
			for (int q = 1; q <= m; q++) {
				if (map[i][q] == 1) {
					cnt = 0;
					if (map[i - 1][q] == -1) cnt++;
					if (map[i + 1][q] == -1) cnt++;
					if (map[i][q - 1] == -1) cnt++;
					if (map[i][q + 1] == -1) cnt++;

					if (cnt >= 2) {
						changelist.push({ i, q });
						//printf("%d %d %d\n", phase, i, q);
					}
				}
			}
		}
		while (!changelist.empty()) {
			//printf("change %d\n", phase);
			crd curr = changelist.front();
			DFS1(curr.x, curr.y);
			changelist.pop();
			remain--;
		}
	}

	printf("%d", phase);

}