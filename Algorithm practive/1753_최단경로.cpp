#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1753_최단경로 ----

	기본 아이디어 : 모두 가중치가 10 이하이므로, 다익스트라 알고리즘을 사용한다.
	vertex의 수가 매우 많기 때문에 이차원 배열로 표현할 수 없다.
	따라서 list의 배열로 graph를 표현한다.

	여기서, list는 해당 배열의 위치를 시작지점으로 하는 간선들의 정보를 담는다.
	*/

/*
	복기해야 할 내용 : 다익스트라는 탐색을 안한 항들 중 최소를 찾기 위해, 우선순위 큐(최소힙)을 사용한다.
	이를 통해서 노드를 찾는 데 걸리는 시간 복잡도가 O(N)에서 O(logN)이 되고, 이 차이로 문제를 풀 수 있게 된다.
*/

#include<stdio.h>
#include<list>
#include<queue>
#define INF 12345678;
using namespace std;

typedef struct _node {
	int num;
	int dist;
}node;

typedef struct _edge {
	int destination;
	int distance;
}edge;

struct cmp {
	bool operator()(node a, node b) {
		return a.dist > b.dist;
	}
};


priority_queue<node, vector<node>, cmp> fordij;

int v, e, start;

list<edge> graph[20020];
bool checked[20020];
int dist[20020];


void Init() {
	for (int i = 1; i <= v; i++) dist[i] = INF;
}

void InitInput() {
	scanf("%d %d %d", &v, &e, &start);
	Init();

}

void graphInput() {
	for (int _ = 0; _ < e; _++) {
		int start, dest, dist;
		scanf("%d %d %d", &start, &dest, &dist);
		graph[start].push_back({ dest, dist });
	}
}

int findmin() {
	/*
	int min = INF;
	int address = -1;
	for (int i = 1; i <= v; i++) {
		if (dist[i] < min && checked[i] == false) {
			min = dist[i];
			address = i;
		}
	}*/

	while (!fordij.empty()) {
		node curr = fordij.top();
		int node_num = curr.num;
		if (checked[node_num] == false) return node_num;
		fordij.pop();
	}

	return -1;
}


void dijkstra(int start) {
	int current = start;
	dist[current] = 0;

	while (current > 0) {
		list<edge> edges = graph[current];
		for (list<edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
			int distance = iter->distance;
			int destination = iter->destination;
			if (dist[current] + distance < dist[destination]) {
				dist[destination] = dist[current] + distance;
				fordij.push({ destination, dist[destination] });
			}
		}
		checked[current] = true;
		current = findmin();
	}
}

int main() {
	InitInput();
	graphInput();
	dijkstra(start);

	for (int i = 1; i <= v; i++) {
		if (dist[i] == 12345678) puts("INF");
		else printf("%d\n", dist[i]);
	}
}