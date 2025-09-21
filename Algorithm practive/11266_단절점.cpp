#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11266_������ ----
	
	������ : Ÿ�� �˰��� (������ ���ϱ�) �� ���ؼ� ����.

	1. ������ ��带 ���������� �Ͽ� DFS�� ������. Ž�� ������ ���� stack�� ��ȣ�� �����ϸ�,
	DFS���� �湮 ������ ���̷� �ϴ� DFS Ʈ���� ������.(����ϴ� ��� ���)

	-> ���⼭, �湮 ������ �ش� �湮 ��尡 ���° �湮 ��������� �̾߱���. ���������� �湮�ؾ��ϴ� ����� ���� �ƴ�.

	2. DFS Ʈ���� ���� ������ �Ϸ�Ǿ��� ���, ��Ʈ���� ��ȸ�ϸ� ������ ã�´�.
	���� :  ��Ʈ����� ��� : 2�� �̻��� �ڽ��� ������ �ִ°�?
			��Ʈ ��尡 �ƴ� ��� : �ڽ� �� �ϳ��� �θ� ��庸�� ��ȣ�� ������?

	
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