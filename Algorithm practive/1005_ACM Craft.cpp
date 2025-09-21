#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1005_ACM Craft ----

	���� �� �ִ� �ǹ��� ���ڰ� ������ ���� : �� ���� ���Ұ� ���踦 ���ϰ� ����
	:: ���� ������ ����� �� �ִ�.



	-> A�� ����� B�� ���� �� �ִ� : a->b�� ����
	�� ���� �׷����� �׸� ��, ���԰����� 0���� ������ Ž���Ұ�� ���� �� �ִ�.
	�ð� �������� : 0(�ƿ� ������ ���غ�) �̰ų�, ����� �ð����� �� ���� �ð��� �� �� �ִ°�� ������.
*/

#include<stdio.h>
#include<queue>
using namespace std;

int t, n, k, w;
bool graph[1005][1005] = {};
int destLine[1005] = {};
int dist[1005] = {};
int weight[1005] = {};
bool visited[1005] = {};

queue<int> forTSort;

void Init() {
	for(int i = 1; i < 1005; i++){
		dist[i] = -1;
		destLine[i] = 0;
		visited[i] = false;
		for (int q = 0; q < 1005; q++) {
			graph[i][q] = false;
		}
	}

	while (!forTSort.empty())forTSort.pop();
}

void topSort() {
	for (int i = 1; i <= n; i++) {
		if (destLine[i] == 0) { 
			dist[i] = 0;
			forTSort.push(i); 
		}
	}
	//puts("");
	while (!forTSort.empty()) {
		int curr = forTSort.front();
		//printf("%d\n", curr);
		if (curr == w) return;
		visited[curr] = true;

		for (int i = 1; i <= n; i++) {
			if (visited[i] == false && graph[curr][i] == true) {
				if (dist[i] == -1 || dist[i] < dist[curr] + weight[curr])
					dist[i] = dist[curr] + weight[curr];
				destLine[i]--;

				if (destLine[i] == 0)forTSort.push(i);
			}
		}
		forTSort.pop();
	}
}

int main() {
	scanf("%d", &t);
	for (int _ = 0; _ < t; _++) {
		Init();
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%d", weight + i);
		for (int _ = 0; _ < k; _++) {
			int x, y; scanf("%d %d", &x, &y);
			graph[x][y] = true;
			destLine[y] ++;
		}
		scanf("%d", &w);

		topSort();
		printf("%d\n", dist[w] + weight[w]);

	}

}