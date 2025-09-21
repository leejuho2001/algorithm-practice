#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11266_단절점 ----
	
	단절점 : 타잔 알고리즘 (단절점 구하기) 를 통해서 구함.

	1. 임의의 노드를 시작점으로 하여 DFS를 진행함. 탐색 순서에 따라 stack에 번호를 저장하며,
	DFS에서 방문 순서를 높이로 하는 DFS 트리를 생성함.(기록하는 방식 사용)

	-> 여기서, 방문 순서는 해당 방문 노드가 몇번째 방문 노드인지를 이야기함. 시작점부터 방문해야하는 노드의 수가 아님.

	2. DFS 트리에 대한 전개가 완료되었을 경우, 루트부터 순회하며 조건을 찾는다.
	조건 :  루트노드일 경우 : 2개 이상의 자식을 가지고 있는가?
			루트 노드가 아닐 경우 : 자식 중 하나라도 부모 노드보다 번호가 낮은가?

	
*/

#include<stdio.h>
#include<list>
using namespace std;


int v, e, rootFind, root;
int cntt = 1;
int cnt;
int visited[10050];
int childnum[10050];
bool isNotArti[10050];

list<int>graph[10050];
list<int>result;

void graphInput() {
	int a, b;
	for (int i = 0; i < e; i++) {
		scanf("%d %d", &a, &b);

		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}


int DFS(int curr, int parent, bool isRoot) {
	//printf("%d ", curr);
	visited[curr] = cntt;
	int rootCnt=0;
	int canGo = cntt++;
	int MinNode = 100000;
	bool case2 = false;
	bool isLeaf = true;
	for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
		
		if (visited[*iter] == 0) {
			isLeaf = false;
			//printf("%d -> %d\n", curr, *iter);
			if (isRoot == true) rootCnt++;

			int temp = DFS(*iter, curr, false);
			if (temp < MinNode) MinNode = temp;
			if (temp >= visited[curr]) case2 = true;
			//printf("%d ->%d, res : %d\n", curr, *iter, temp);
		}
		
		else if (*iter != parent)
			if (visited[*iter] < canGo) canGo = visited[*iter];
	}
	if (isLeaf == true) isNotArti[curr] = true;
	else if (isRoot == true && rootCnt <= 1)  isNotArti[curr] = true;
	else if(isRoot != true)
		if (!case2) isNotArti[curr] = true;
	//printf("%d :: %d - %d\n", curr, visited[curr], MinNode);
	return canGo<MinNode?canGo:MinNode;
}

void tarjan() {
	for (int i = 1; i <= v; i++) {
		if (visited[i] == 0) { 
			rootFind = 0;
			root = cntt;
			DFS(i, 0, true); 
			//puts("");
		}
	}
}

int main() {

	scanf("%d %d", &v, &e);
	graphInput();
	tarjan();

	for (int i = 1; i <= v; i++) {
		if (isNotArti[i] == false) {
			result.push_back(i);
			cnt++;
		}
	}

	printf("%d\n", cnt);
	for (list<int>::iterator iter = result.begin(); iter != result.end(); iter++) {
		printf("%d ", *iter);
	}
}