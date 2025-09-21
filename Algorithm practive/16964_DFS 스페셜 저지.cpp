#define _CRT_SECURE_NO_WARNINGS

/*
	--- 16964 DFS 스페셜 저지 ---

	idea
	필요한 정보 : 시작점 기준, 각 노드들의 깊이
		-> 요구 자료구조 : 그래프(리스트), 큐
		-> 사용 알고리즘 : BFS

	방법 : 방문순서 SEQUENCE를 하나씩 보면서 시작함.
	시작노드 -> 도착노드
	
	거리(시작노드) < 거리(도착노드) 인 경우
	거리노드 - 도착노드 인 edge를 하나 찾는다. :: 이진탐색 사용

	거리(시작노드) < 거리(도착노드) 인 경우
	a. 시작노드에서 남아있는 edge의 개수가 몇개인지 확인한다.
		-> edge의 개수가 1개 이상인 경우 False를 반환하면 된다.
	
	b. 도착노드의 거리 -1인 노드까지 백트래킹
		이 중에 a과정을 반복해줌.

	주의사항
	:: a-b 방향의 탐색을 할 경우
	a,b의 edge 개수를 모두 - 해줘야함
*/


#include<stdio.h>
#include<list>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

typedef struct edg {
	int s;
	int e;
}edge;

int n; //nodeNum
list<int> graph[100005];
edge edgelist[200010];

int nodeseq[100005];
int depth[100005];
int remainEdgeNum[100005];

stack<int> forDFS;
queue<int> forBFS;

void BFS(int s);
int CompEdge(edge a, edge b);
bool Comp(edge a, edge b);
int biSearchEdge(edge target);
bool prove();

int main() {
	scanf("%d", &n);
	int s, e;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &s, &e);
		edgelist[i - 1].s = s;
		edgelist[i - 1].e = e;
		edgelist[n + i - 2].s = e;
		edgelist[n + i - 2].e = s;
		graph[s].push_back(e);
		graph[e].push_back(s);
		remainEdgeNum[s]++;
		remainEdgeNum[e]++;
	}

	for (int i = 0; i < n;i++) {
		scanf("%d", nodeseq + i);
	}
	sort(edgelist, edgelist + (2 * n - 2), Comp);

	//ss
	//for (int i = 0; i < 2 * (n - 1); i++) {
	//	printf("edge :: %d - %d\n", edgelist[i].s, edgelist[i].e);
	//}
	//ee

	BFS(1);

	//ss
	//puts("depths");
	//for (int i = 1; i <= n;i++)printf("%d ", depth[i]);
	//puts("");
	//ee

	//ss
	//puts("nodeseq");
	//for (int i = 0; i < n; i++)printf("%d ", nodeseq[i]);
	//puts("");
	//ee

	bool res = prove();

	if (res == true) puts("1");
	else puts("0");
}


void BFS(int s) {
	depth[s] = 1;
	forBFS.push(s);
	int curr;
	while (!forBFS.empty()) {
		curr = forBFS.front();
		for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
			if (depth[*iter] == 0) {
				depth[*iter] = depth[curr] + 1;
				forBFS.push(*iter);
			}
		}

		forBFS.pop();
	}
} // depth 측정을 위한 BFS

int CompEdge(edge a, edge b) {
	if (a.s == b.s) {
		if (a.e < b.e) return -1;
		else if (a.e == b.e) return 0;
		else return 1;
	}
	if (a.s < b.s) return -1;
	else return 1;
} // 왼쪽이 크면 -1, 동일하면 0, 오른쪽이 크면 1

bool Comp(edge a, edge b) {
	return CompEdge(a, b) == -1;
} // 오름차순용 compare

int biSearchEdge(edge target) {
	int s = 0;
	int e = 2 * n - 3;

	int cent;

	while (e >= s) {
		cent = (s + e) / 2;
		if (CompEdge(target, edgelist[cent]) == -1) {
			e = cent - 1;
		} // target이 더 작으면
		else if (CompEdge(target, edgelist[cent]) == 0) {
			return cent;
		}
		else {
			s = cent + 1;
		}
	}

	return -1;
} // 해당하는 edge찾기

bool prove() {
	int seqOff = 0;
	if (nodeseq[0] != 1) return false;
	forDFS.push(1);
	while (seqOff < n-1) {
		int s = nodeseq[seqOff];
		int e = nodeseq[seqOff+1];
		//ss
		//printf(":: depth comp :: s = %d, %d| e = %d, %d\n", s, depth[s], e, depth[e]);
		//ee
		if (depth[e] <= depth[s]) {
			//ss
			//printf(":: remainEdges :: s = %d, %d| e = %d, %d\n", s, remainEdgeNum[s], e, remainEdgeNum[e]);
			//ee
			if (remainEdgeNum[s] > 0) return false;
			else {
				while (depth[forDFS.top()] >= depth[e]) {
					if (remainEdgeNum[forDFS.top()] > 0) return false;
					forDFS.pop();
				}
				if (remainEdgeNum[forDFS.top()] > 0 && biSearchEdge({ forDFS.top(),e }) != -1) {
					remainEdgeNum[forDFS.top()]--;
					remainEdgeNum[e]--;

					forDFS.push(e);
					seqOff++;
				}
				else return false;
			}
		}
		else {
			if (remainEdgeNum[s] > 0 && biSearchEdge({ s, e }) != -1) {
				remainEdgeNum[s] --;
				remainEdgeNum[e] --;
				forDFS.push(e);
				//ss
				//printf("traveled :: %d -> %d \n", s, e);
				//ee
				seqOff++;
			}

			else return false;
		}
	}
	return true;
}

