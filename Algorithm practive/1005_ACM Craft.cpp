#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1005_ACM Craft ----

	지을 수 있는 건물의 숫자가 정해져 있음 : 두 개의 원소가 관계를 강하게 가짐
	:: 위상 정렬을 사용할 수 있다.



	-> A를 지어야 B를 지을 수 있다 : a->b인 간선
	을 통한 그래프를 그린 뒤, 진입간선이 0개인 노드부터 탐색할경우 구할 수 있다.
	시간 갱신조건 : 0(아예 도착을 안해봄) 이거나, 저장된 시간보다 더 적은 시간을 쓸 수 있는경우 갱신함.
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