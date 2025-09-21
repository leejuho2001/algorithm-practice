#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1197_�ּ� ���д� Ʈ��_prq ----
	���� �˰��򿡼� �ʿ��� ���� :
	checked�� ������ ������, '�ּ�'�� edge�� ã��
	--> �ٽ��� �ּ��ϰ�, ���� �켱���� ť(�ּ� ��)�� ����� �� ����.

	checked�� ���� edge�� ���, �� Ž���� ������ �����Ƿ� pop�� �ص� ��.

	--> ���� Ž�� �������� �߻��ϴ� ����� ���� Ȯ �ٰԵ�.
	*/

/*#include<stdio.h>
#include<queue>
#include<list>
using namespace std;



typedef struct _edge {
	int dest;
	int weight;
}edge;

struct cmp {
	bool operator()(edge a, edge b) {
		return a.weight > b.weight;
	}
};

bool checked[10005];

int n, m, vertexCnt;
long long int edgeSum;
priority_queue<edge, vector<edge>, cmp> graph[10005];

struct listCmp {
	bool operator()(int a, int b) {
		while (!graph[a].empty() && checked[graph[a].top().dest] == true) graph[a].pop();
		while (!graph[b].empty() && checked[graph[b].top().dest] == true) graph[b].pop();
		
		if (graph[a].empty() && graph[b].empty()) return false;
		else if (graph[b].empty()) return false;
		else if (graph[a].empty()) return true;
		// �� �տ��ִ� prq�� ����ִ� ���, ������ �� ���⶧���� ����ϸ� �ȵȴ�.
		// ���� �տ��ִ� prq�� �� ��� �񱳸� �������� �ʰ� �ٷ� �ڷ� ������.
		// ���� ���ǿ��� ��� ��带 �����ϱ� ������, included�� ���ִ� ���� �� �ϳ� �̻��� ������� �ʴٴ� ���� ������ �Ѵ�.

		return graph[a].top().weight > graph[b].top().weight;
	}
};

priority_queue<int, vector<int>, listCmp> included;


void graphInput() {
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push({ b, c });
		graph[b].push({ a, c });
	}
}

void prim() {
	included.push(1);
	checked[1] = true;
	vertexCnt++;
	int current = 0;
	int edgeLen = 12345678;
	int destination = -1;
	edge currentEdge = {};

	while (vertexCnt < n) {
		edgeLen = 12345678;
		destination = -1;

		current = included.top();
		currentEdge = graph[current].top();
		edgeLen = currentEdge.weight;
		destination = currentEdge.dest;
		//printf("%d %d\n", destination, edgeLen);
		checked[destination] = true;
		if(edgeLen%2)
			edgeSum += (long long int) edgeLen;
		included.push(destination);
		queue<edge>tempQ;
		while (!graph[destination].empty()) {
			tempQ.push(graph[destination].top());
			int tempdest = graph[destination].top().dest;
			while (!graph[tempdest].empty()&&checked[graph[tempdest].top().dest] == true) graph[tempdest].pop();
			graph[destination].pop();
		}
		while (!tempQ.empty()) {
			graph[destination].push(tempQ.front());
			tempQ.pop();
		}
		vertexCnt++;
	}
}

int main() {
	scanf("%d %d", &n, &m);
	graph[0].push({ 0, -9999999 });
	graphInput();
	prim();
	if (vertexCnt < n) printf("-1");
	else printf("%lld", edgeSum);
}*/

#include<stdio.h>
#include<queue>
#include<list>
using namespace std;


typedef struct _edge {
	int dest;
	int weight;
}edge;

struct cmp {
	bool operator()(edge a, edge b) {
		return a.weight > b.weight;
	}
};

priority_queue<edge, vector<edge>, cmp> included;
list<edge>graph[10005];
bool checked[10005];
int n, m, vertexCnt;
long long int edgeSum;

void addInclude(int v) {
	for (list<edge>::iterator iter = graph[v].begin(); iter != graph[v].end(); iter++) {
		edge cur = *iter;
		if (checked[cur.dest] == false) included.push(cur);
	}
}

void prim() {
	vertexCnt = 1;
	checked[1] = true;
	
	addInclude(1);

	while (vertexCnt < n) {
		while (checked[included.top().dest] == true) included.pop();

		edge cur = included.top();
		checked[cur.dest] = true;
		edgeSum += (long long int)cur.weight;
		addInclude(cur.dest);
		vertexCnt++;
	}
}

void graphInput() {
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}
}

int main() {
	scanf("%d %d", &n, &m);
	graphInput();
	prim();

	printf("%d", edgeSum);
}

// included�� ��� ��ȣ�� �ƴ϶� ���� ������ �ִ°��� �ٽ��̾���
// ��带 include�� �����ؼ� ��������.