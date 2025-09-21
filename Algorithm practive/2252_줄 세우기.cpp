#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2252_줄 세우기 ----

	줄을 세운다 :: 위 아래가 존재한다 :: 트리 형태를 가진다.
	트리 형태를 만든 뒤, 탐색시키면 된다.
	트리에 존재하지 않는 경우, 언제 위치하더라도 상관이 없다.

	트리를 만드는 법 :
	최단 거리를 모두 지운다.
	그래프는 방향 그래프로 취급한다.

	역추적으로 루트노드를 찾은 뒤, 순회하는 방식을 사용한다.

*/

#include<stdio.h>
#include<list>
using namespace std;
typedef struct _node {
	int key;
	int edgeCnt;
}node;

int n, m;
list<int>graph[32005];
int nearest[32005];
node edgeCnts[32005];

void make_tree() {

}

void graphinput() {
	int back, front;
	for (int _ = 0; _ < m; _++) {
		scanf("%d%d", &back, &front);

		graph[front].push_back(back);
		edgeCnts[front].edgeCnt++;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i<= n; i++) {
		edgeCnts[i].key = i;
	}
	graphinput();

}