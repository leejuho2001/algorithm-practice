#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1238_파티 ----
	아이디어 : 
	학생이 X번 마을로 가는 데 걸리는 최단거리
	= X번 마을에서 학생이 있는 곳까지 가는 데 걸리는 최단 거리.

	단, 단방향 간선을 가지는 그래프기 때문에, 해당 간선들의 방향을 반대로 입력해주어야함.
	간선의 방향을 반대로 입력한 그래프에서 X번 마을을 시작점으로 하는 BFS를 사용.

	학생이 X번 마을에서 집까지 가는 데 걸리는 최단거리
	= X번 마을에서 학생이 있는 곳까지 가는 데 걸리는 최단거리
	단, 단방향 간선의 방향이 정방향인 그래프에서 BFS를 실시해야함.

	탐색의 기준: 현재까지의 거리가 해당 노드까지의 거리보다 작은가?
	*/
#include<stdio.h>
#include<queue>
#include<list>

using namespace std;
int N, M, X;

typedef struct _edge {
	int node;		// 상대 노드
	int weight;		// 상대 노드까지의 가중치
}edge;

list<edge> reverseGraph[1050];
int reverseDist[1050];
list<edge> graph[1050];
int dist[1050];

queue<int>forBFS;
/*
	---- graph_input ----

	:: action ::
	단방향 그래프를 입력받는다.
	정방향, 역방향 모두 기록한다.
*/
void graph_input() {
	for (int i = 0; i < M; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		edge forward = { b, w };
		edge reverse = { a, w };

		graph[a].push_back(forward);
		reverseGraph[b].push_back(reverse);
	}
}


/*
	---- BFS ----
	:: param ::
	list<int> *graph : 해당 탐색에 그래프로 사용할 리스트의 배열 
	int *DT : 해당 탐색에 DT로 사용할 정수 배열
	int init : 탐색의 시작 지점.

	:: action ::
	init에서 모든 노드에 최단거리에 대한 BFS 탐색을 함.
	노드에 대한 탐색 기준 : 해당 노드까지 걸린 거리가 기존에 저장되어 있는 거리보다 먼가?
							or 해당 노드에 탐색한 기록이 없는가?

	*/

void BFS(list<edge> graph[], int* DT, int init) {
	forBFS.push(init);
	DT[init] = 0;

	while (!forBFS.empty()) {
		int current = forBFS.front();
		list<edge>::iterator iter = graph[current].begin();

		for (iter; iter != graph[current].end(); iter++) {
			if (iter->node == init) continue;
			if (DT[iter->node] > DT[current] + iter->weight || DT[iter->node] == 0) {
				DT[iter->node] = DT[current] + iter->weight;
				forBFS.push(iter->node);
			}
		}

		forBFS.pop();
	}
}

/*
	---- find_max ----
	:: param ::
	test : 각 DT들의 값을 모두 출력하는가에 대한 여부를 입력받음.

	:: action ::
	Dist와 reverseDist의 값을 합친값중 최댓값을 찾는다.
	최댓값은 선형으로 탐색한다.
*/
int find_MAX(bool test) {
	int MAX = 0;
	for (int i = 1; i <= N; i++) {
		int current = reverseDist[i] + dist[i];
		if (test == true) printf("%d %d %d\n", reverseDist[i], dist[i], current);
		if (current > MAX) MAX = current;
	}
	return MAX;
}

int main() {
	scanf("%d %d %d", &N, &M, &X);
	graph_input();
	BFS(reverseGraph, reverseDist, X);
	BFS(graph, dist, X);

	printf("%d", find_MAX(false));
}