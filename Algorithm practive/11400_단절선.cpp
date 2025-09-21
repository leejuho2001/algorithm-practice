#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11400_������ ----

	�ٽ� ���̵�� 1: ���� ���� �� ������ �����ϴ� �� ��尡 ��� �������� ��
	�ش� ������ �������� �ȴ�.

	����, ��� �������� ���� ��, �ش� �������鿡 ���� ����� �������� ����, ����� ��尡
	�������̶��, �ش� ������ ���������� ����� �� �ִ�.

	--> ���� :: 1�� 2�� �����ϴ� ���� 1���� �ִ� �׷����� �����غ���, 
	�� �� �������̶�� �� �� ������ �� ���� �մ� ������ �������̴�. ���� �� ������ ��� �Ұ�.



	�ٽ� ���̵�� 2: 
	�ش� ���� ���ϴ� ������ �������� �Ǳ� ���ؼ�??
	-> �ش� ��� ���ķ� Ž���ϴ� ��� ��尡 �ش� ��� ���� �� �����Ѵ�.

	����, ����ϰ��ִ� DFS���� �ڽĳ�带 Ž���ϸ鼭 �ش� �ڽĳ�尡 ���� ��庸�� ���� ���θ� �� �� �ִٸ�,
	�ش� �ڽĳ��� �̾����� ������ 

*/

#include<stdio.h>
#include<algorithm>
#include<queue>
#include<list>
using namespace std;

typedef struct edge {
	int start;
	int end;
}edg;

struct cmp {
	bool operator()(edge a, edge b) {
		if (a.start == b.start) return a.end > b.end;
		else return a.start > b.start;
	}
};

priority_queue<edge, vector<edge>, cmp> answer;
list<int>graph[100050];

int visited[100050];
bool isNotArti[100050];
int v, e, cntt=1;
int rootCnt;

void graphinput() {
	int a, b;
	for (int i = 0; i < e; i++) {
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

int DFS_tarj(int current, int parent, bool isRoot) {
	int minChildResult = 10000000;
	int smallestIndexCanGo = cntt;
	bool subGraphNotExist = true;
	bool isLeaf = true;
	visited[current] = cntt++;
	int curr = 0;
	for (list<int>::iterator iter = graph[current].begin(); iter != graph[current].end(); iter++) {
		curr = *iter;
		if (visited[curr] == 0) {
			isLeaf = false;
			if (isRoot == true) rootCnt++;
			int temp = DFS_tarj(curr, current, false);
			if (temp < minChildResult) minChildResult = temp;
			if (temp >= visited[current]) {
				subGraphNotExist = false; 
				if (temp > visited[current]) {
					if(current>curr)
						answer.push({ curr, current });
					else
						answer.push({ current, curr });
				}
			}
		}

		else if (curr != parent) {
			if(visited[curr]<smallestIndexCanGo)
				smallestIndexCanGo = visited[curr];
		}
	}
	if (isLeaf == true) isNotArti[current] = true;
	else if (isRoot == true) {
		if (rootCnt <= 1) isNotArti[current] = true;
	}
	else if (subGraphNotExist == true) isNotArti[current] = true;

	return smallestIndexCanGo < minChildResult ? smallestIndexCanGo : minChildResult;

}

void tarjan() {
	for (int i = 1; i <= v; i++) {
		if (visited[i] == 0) { 
			rootCnt = 0;
			DFS_tarj(i, 0, true); 
		}
	}
}


int main() {
	scanf("%d %d", &v, &e);
	graphinput();
	tarjan();
	/*
	for (int i = 1; i <= v; i++) {
		if (isNotArti[i] == false) {
			for (list<int>::iterator iter = graph[i].begin(); iter != graph[i].end(); iter++) {
				if (isNotArti[*iter] == false && *iter > i)
					answer.push({ i, *iter });
			}
		}
	}*/

	/*
	for (int i = 1; i <= v; i++) {
		printf("%d ", isNotArti[i]);
	}puts("");
	*/

	printf("%d\n", answer.size());
	while (!answer.empty()) {
		edge cur = answer.top();
		printf("%d %d\n", cur.start, cur.end);
		answer.pop();
	}
}