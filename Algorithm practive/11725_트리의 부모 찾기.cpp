#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11725_트리의 부모 찾기 ----

	아이디어 : BFS를 통해 트리를 탐색함.
	1이 트리의 루트노드로 정해지기 때문에 1과의 최소 거리를 
	1과의 최소 거리를 찾기 위해선 DFS보단 BFS를 사용함.

	노드의 수가 최대 100000개이기 때문에 그래프를 2차원 배열로 표현하지 않고,
	리스트의 배열을 통해 표현함.

	*/


#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

list<int> graph[100050];
queue<int>forBFS;
int parent[100050];

int n;


/*
	---- graph_input ----
	:: param ::
	없음.

	:: action ::
	양방향 그래프를 만듬
	하나의 간선이 입력되면 간선의 각 엣지에 해당하는 리스트에 상대 엣지에 대한 정보를 추가함.
*/
void graph_input() {
	for (int _ = 0; _ < n-1; _++) {
		int p, q;
		scanf("%d %d", &p, &q);

		graph[p].push_back(q);
		graph[q].push_back(p);
	}
}

/*
	---- BFS ----

	:: param ::
	int init_node : 시작 노드의 번호.

	:: Action ::
	너비우선탐색을 실시함. parent에 부모노드가 기록됩지 않은 경우 탐색
*/

void BFS(int init_node) {
	forBFS.push(init_node);
	parent[init_node] = -1;

	while (!forBFS.empty()) {
		int current = forBFS.front();
		list<int> currentList = graph[current];
		list<int>::iterator iter = currentList.begin();
		for (iter; iter != currentList.end(); iter++) {
			if (parent[*iter] == 0) {
				parent[*iter] = current;
				forBFS.push(*iter);
			}
		}
		forBFS.pop();
	}
}

int main() {
	scanf("%d", &n);
	graph_input();
	BFS(1);

	for (int i = 2; i <= n; i++) {
		printf("%d\n", parent[i]);
	}
}