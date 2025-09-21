#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1197_최소 스패닝 트리_prq ----
	프림 알고리즘에서 필요한 정보 :
	checked에 속하지 않으며, '최소'인 edge를 찾음
	--> 핵심은 최소일것, 따라서 우선순위 큐(최소 힙)을 사용할 수 있음.

	checked에 속한 edge의 경우, 더 탐색할 이유가 없으므로 pop을 해도 됨.

	--> 간선 탐색 과정에서 발생하는 계산의 양이 확 줄게됨.
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
		// 맨 앞에있는 prq가 비어있는 경우, 간선이 더 없기때문에 고려하면 안된다.
		// 따라서 앞에있는 prq가 빈 경우 비교를 진행하지 않고 바로 뒤로 보낸다.
		// 문제 조건에서 모든 노드를 연결하기 때문에, included에 들어가있는 노드들 중 하나 이상은 비어있지 않다는 것을 전제로 한다.

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

// included에 노드 번호가 아니라 간선 정보를 넣는것이 핵심이었음
// 노드를 include에 저장해서 꼬여버림.