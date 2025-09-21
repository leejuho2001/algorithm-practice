#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11400_단절선 ----

	핵심 아이디어 1: 단절 선은 그 간선을 구성하는 두 노드가 모두 단절점일 때
	해당 간선이 단절선이 된다.

	따라서, 모든 단절점을 구한 뒤, 해당 단절점들에 대해 연결된 간선들을 보고, 연결된 노드가
	단절점이라면, 해당 간선을 단절선으로 취급할 수 있다.

	--> 예외 :: 1과 2를 연결하는 간선 1개만 있는 그래프를 생각해보면, 
	둘 다 단절점이라고 할 수 없으나 그 둘을 잇는 간선은 단절선이다. 따라서 위 가정은 사용 불가.



	핵심 아이디어 2: 
	해당 노드로 향하는 간선이 단절선이 되기 위해선??
	-> 해당 노드 이후로 탐색하는 모든 노드가 해당 노드 위로 못 가야한다.

	따라서, 사용하고있는 DFS에서 자식노드를 탐색하면서 해당 자식노드가 현재 노드보다 작은 노드로만 갈 수 있다면,
	해당 자식노드로 이어지는 간선은 

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