#define _CRT_SECURE_NO_WARNINGS
/*
	2623_음악 프로그램
	일부 프로그램들의 순서가 정해지고, 그 순서를 지키는 순서를 출력해야하는 문제
	-> 줄 세우기와 같은 문제에 해당함 == 위상정렬을 사용할 수 있음.

	불가능한 경우도 존재 -> 방향그래프에서 사이클이 생성될 경우 모든 노드에 대해 위상정렬이 되지 않음.
	따라서, 모든 노드에 대해 위상정렬이 되지 않을경우, 순서를 정할 수 없는 상태.
	따라서 queue 사이즈 != 노드 갯수일 경우 0을 출력함.
*/


#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

list<int>graph[1005];
queue<int>forTPS, answer;
int entLine[1005];
int n, m;

void topologic_sort() {
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		if (entLine[i] == 0) {
			forTPS.push(i);
		}
	}

	while (!forTPS.empty()) {
		cur = forTPS.front();
		for (list<int>::iterator iter = graph[cur].begin(); iter != graph[cur].end(); iter++) {

		}
	}
}