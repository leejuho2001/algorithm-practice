#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1753_�ִܰ�� ----

	�⺻ ���̵�� : ��� ����ġ�� 10 �����̹Ƿ�, ���ͽ�Ʈ�� �˰����� ����Ѵ�.
	vertex�� ���� �ſ� ���� ������ ������ �迭�� ǥ���� �� ����.
	���� list�� �迭�� graph�� ǥ���Ѵ�.

	���⼭, list�� �ش� �迭�� ��ġ�� ������������ �ϴ� �������� ������ ��´�.
	*/

/*
	�����ؾ� �� ���� : ���ͽ�Ʈ��� Ž���� ���� �׵� �� �ּҸ� ã�� ����, �켱���� ť(�ּ���)�� ����Ѵ�.
	�̸� ���ؼ� ��带 ã�� �� �ɸ��� �ð� ���⵵�� O(N)���� O(logN)�� �ǰ�, �� ���̷� ������ Ǯ �� �ְ� �ȴ�.
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