#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1197_최소 스패닝 트리 ----
	프림 알고리즘을 사용함.
	1. 하나의 노드에서부터 시작함
	2. 가지고 있는 간선 중 포함된 노드가 아닌 노드와 연결된 최소 노드와 연결.


	-> 노드의 수가 많음 : 연결리스트의 배열 형태로 그래프를 표현.
	::: 결과 --> 시간초과.
	*/

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int v, E;

typedef struct _dege {
	int dest;
	int weight;
}edge;

struct cmp {
	bool operator()(edge a, edge b) {
		return a.weight > b.weight;
	}
};

list<edge>graph[10003];
list<int> included;
bool checked[10003];

int vertexCnt = 0;
long long int edgeSum = 0;

/*
	---- input ----
	:: Action ::
	간선 수 E 만큼 간선을 입력받음.
	방향 그래프가 아니므로, s와 e 모두에 반대 번호를 destination으로하는 edge 정보를 저장.
*/
void input() {
	
	for (int _ = 0; _ < E; _++) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		graph[s].push_back({ e, w });
		graph[e].push_back({ s, w });
	}
}

/*
	---- prim ----

	:: Action ::
	1을 시작 노드로 하여 프림 알고리즘을 실시함.
*/


void prim() {
	included.push_back(1);
	checked[1] = true;
	vertexCnt++;

	while (vertexCnt < v) {
		int edgeLen = 12345678;
		int destination = -1;
		for (list<int>::iterator node = included.begin(); node != included.end(); node++) {
			for (list<edge>::iterator edg = graph[*node].begin(); edg != graph[*node].end(); edg++) {
				if (checked[edg->dest] == false && edg->weight < edgeLen) {
					edgeLen = edg->weight;
					destination = edg->dest;
				}
			}
		}

		if (destination == -1) break;
		else {
			//printf("%d %d\n", destination, edgeLen);

			edgeSum += (long long int)edgeLen;
			included.push_back(destination);
			checked[destination] = true;
			vertexCnt++;
		}
	}
}




int main() {
	scanf("%d %d", &v, &E);
	input();
	prim();
	if (vertexCnt < v) printf("-1");
	else printf("%lld", edgeSum);
}