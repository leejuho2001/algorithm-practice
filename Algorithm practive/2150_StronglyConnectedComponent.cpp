#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2150_StronglyConnectedComponent ----

	-- 코사라주 알고리즘을 사용하는 것을 목표로 한다.

	1. 방향이 역인 그래프에서 임의의 점을 시작노드로 DFS를 시행한다.
	여기서 방문하는 순서대로 스택에 넣는다.

	2. 기존 그래프에서 1에서 스택에 저장한 노드 순으로 DFS를 실행한다.
	여기서, DFS로 탐색하는 모든 노드들이 
*/

#include<stdio.h>
#include<stack>
#include<queue>
#include<list>
using namespace std;

struct cmp {
	bool operator()(int a, int b) {
		return a > b;
	}
};

struct qcmp {
	bool operator()(queue<int> a, queue<int> b) {
		return a.front() > b.front();
	}
};
priority_queue<int, vector<int>, cmp> forKOS;
priority_queue<queue<int>, vector<queue<int>>, qcmp> answers;
stack<int> saveDFS;

list<int>graph[10050];
list<int>reverseGraph[10050];

int visited[10050];

int v, e, cnt;

void graphInput() {
	int s, en;
	for (int i = 0; i < e; i++) {
		scanf("%d %d", &s, &en);
		graph[s].push_back(en);
		reverseGraph[en].push_back(s);
	}
}

void DFS(int index) {
	forKOS.push(index);
	visited[index] = 2;
	for (list<int>::iterator iter = graph[index].begin(); iter != graph[index].end(); iter++)
		if (visited[*iter] != 2) DFS(*iter);
}

void revDFS(int index) {
	visited[index] = 1;

	for (list<int>::iterator iter = reverseGraph[index].begin(); iter != reverseGraph[index].end(); iter++) {
		if (visited[*iter] != 1) { 
			revDFS(*iter); 
		}
	}
	saveDFS.push(index);
}

void Kos() {
	for (int i = 1; i <= v; i++) {
		if (visited[i] != 1) revDFS(i);
	}

	while (!saveDFS.empty()) {
		int curr = saveDFS.top();
		if (visited[curr] != 2) {
			queue<int> answer;
			cnt++;
			DFS(curr);
			
			while (!forKOS.empty()) {
				answer.push(forKOS.top());
				forKOS.pop();
			}

			answer.push(-1);
			answers.push(answer);
		}

		saveDFS.pop();
	}
}


int main() {
	scanf("%d %d", &v, &e);

	graphInput();
	Kos();
	printf("%d\n", cnt);
	while (!answers.empty()) {
		queue<int>curr = answers.top();
		while (!curr.empty()) {
			printf("%d ", curr.front());
			curr.pop();
		}
		puts("");
		answers.pop();
	}
}


