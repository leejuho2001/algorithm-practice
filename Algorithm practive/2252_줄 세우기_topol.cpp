#define _CRT_SECURE_NO_WARNINGS

/*
	2252_줄 세우기_topol

	1. 크기 관계는 유향 그래프다
	2. 상대적인 크기로 그래프가 정의되는 경우, 사이클이 발생할 수 없다.
	 :::: A>B>C>A 가 불가능하기 때문.

	---->> 위상정렬을 사용할 수 있다.
	==>> 위상정렬은 각 원소의 연관성이 깊은 자료에 대해 활용하기 좋다.

	
*/

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int n, m;

queue<int>forTPS;
bool visited[32050] = {};
list<int>graph[32050] = {};
int inDeg[32050] = {};


void topology_q() {
	int curr, curr2;
	while (!forTPS.empty()) {
		curr = forTPS.front();
		for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
			curr2 = *iter;
			if (visited[curr2] == false && inDeg[curr2] > 0) {
				inDeg[curr2]--;
				if (inDeg[curr2] == 0) {
					forTPS.push(curr2);
					visited[curr2] = true;
				}
			}
		}
		printf("%d ", curr);
		forTPS.pop();
	}
	
}

void graphInit() {
	int p, q;
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &p, &q);
		graph[p].push_back(q);
		inDeg[q]++;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	graphInit();
	for (int i = 1; i <= n; i++) {
		if (visited[i] == false && inDeg[i] == 0) {
			forTPS.push(i);
			visited[i] = true;
			topology_q();
		}
	}
}