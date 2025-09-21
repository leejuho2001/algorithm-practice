#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1238_��Ƽ ----
	���̵�� : 
	�л��� X�� ������ ���� �� �ɸ��� �ִܰŸ�
	= X�� �������� �л��� �ִ� ������ ���� �� �ɸ��� �ִ� �Ÿ�.

	��, �ܹ��� ������ ������ �׷����� ������, �ش� �������� ������ �ݴ�� �Է����־����.
	������ ������ �ݴ�� �Է��� �׷������� X�� ������ ���������� �ϴ� BFS�� ���.

	�л��� X�� �������� ������ ���� �� �ɸ��� �ִܰŸ�
	= X�� �������� �л��� �ִ� ������ ���� �� �ɸ��� �ִܰŸ�
	��, �ܹ��� ������ ������ �������� �׷������� BFS�� �ǽ��ؾ���.

	Ž���� ����: ��������� �Ÿ��� �ش� �������� �Ÿ����� ������?
	*/
#include<stdio.h>
#include<queue>
#include<list>

using namespace std;
int N, M, X;

typedef struct _edge {
	int node;		// ��� ���
	int weight;		// ��� �������� ����ġ
}edge;

list<edge> reverseGraph[1050];
int reverseDist[1050];
list<edge> graph[1050];
int dist[1050];

queue<int>forBFS;
/*
	---- graph_input ----

	:: action ::
	�ܹ��� �׷����� �Է¹޴´�.
	������, ������ ��� ����Ѵ�.
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
	list<int> *graph : �ش� Ž���� �׷����� ����� ����Ʈ�� �迭 
	int *DT : �ش� Ž���� DT�� ����� ���� �迭
	int init : Ž���� ���� ����.

	:: action ::
	init���� ��� ��忡 �ִܰŸ��� ���� BFS Ž���� ��.
	��忡 ���� Ž�� ���� : �ش� ������ �ɸ� �Ÿ��� ������ ����Ǿ� �ִ� �Ÿ����� �հ�?
							or �ش� ��忡 Ž���� ����� ���°�?

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
	test : �� DT���� ���� ��� ����ϴ°��� ���� ���θ� �Է¹���.

	:: action ::
	Dist�� reverseDist�� ���� ��ģ���� �ִ��� ã�´�.
	�ִ��� �������� Ž���Ѵ�.
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