#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11438_LCA2 ----
	Ʈ�� : �������踦 ������ ����.
	+ ���� ���� : 1�� ��尡 ��Ʈ����� �־���.

	-> ���� Ž�� 1ȸ(BFS)�� ���� �� ���鰣�� �������踦 �� �� ����.
	����, parent() ��带 ���ؼ� �ش� ��ȣ ����� �θ��尡 �������� ������ �� �ִ�.
	
	�������� Ž�� ���
	1. level�� �� ū ��带 ����Ű�� �ִ� �����͸� �� ����� �θ�� �ű��.
	2. level�� �������, ���� ��带 ����Ű���� Ȯ���ϰ� �׷��� ������� �Լ� ���� ���� ��带 ���� Ž���Ѵ�.
	3. ���� ��带 ����Ű�� return�Ѵ�.

	#�ð��ʰ�.
	����Ʈ���� ���°� �ƴ�, ����Ʈ���� ���°� �ƴϹǷ� ���� ���� Ž�� �������� O(logN)�� ������ �� ����.
	----- idea1.


	�ش� ������ �ذ��� ����, ������ log n�� ���⵵�� ������ �˰����� ����ؾ���.
	-> ���̿� ���� �̺�Ž���� ���¸� ����� �� ����.

	�̺� Ž���� �ϱ� ����, Ʈ���� DT�� ����� (DFS�� ���� 2^n��° ������ �� �� ����.

	�̺�Ž�� ��� :
	-> ���ϴ� ���� ������ �ִ� ũ���� 2^n�� �������� �ϴ� �̺�Ž���� �����.


	���� :
	�� ���� ���̿� �ִ� ��带 ���� ���̿� �ִ� ���� ���߱� ( ���⼭�� �ִ� 2^n)�� �����.

	�׸��� LCA�� ���̿� ���� �̺�Ž������ ã��.

	DFS���� ��� �����带 ã�°�?
	-> 


*/


/*
#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

queue<int>forBFS;
bool visited[100050];
int parent[100050];
int level[100050];

list<int> graph[100050];

void BFS() {
	forBFS.push(1);
	level[1] = 1;
	visited[1] = true;
	while (!forBFS.empty()) {
		int curr = forBFS.front();
		for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
			if (visited[*iter] == false) {
				visited[curr] = true;
				forBFS.push(*iter);
				parent[*iter] = curr;
				level[*iter] = level[curr] + 1;
			}
		}
		forBFS.pop();
	}
}
// tree build�� BFS

void graphInput(int n) {
	int a, b;
	for (int _ = 1; _ < n; _++) {
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

int find_LCA(int l, int r) {
	int templ = l;
	int tempr = r;

	while (templ != tempr) {
		if (level[templ] >= level[tempr]) templ = parent[templ];
		if (level[tempr] > level[templ]) tempr = parent[tempr];
	}
	return templ;
}

int main() {
	int n, m; scanf("%d", &n);
	graphInput(n);
	BFS();
	scanf("%d", &m);
	int l, r;
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &l, &r);
		printf("%d\n", find_LCA(l, r));
	}
}
*/ //idea 1

#include<stdio.h>
#include<math.h>
#include<list>
using namespace std;


list<int> graph[100005];
int parents[100005][17];
int heights[100005];
// height : �ش� ����� ���̸� ��ȯ.
int temp[100005];

int n, m;
int left, right;
int LCA;


void DFS_Topar(int nodeNum, int height) {
	heights[nodeNum] = height;
	temp[height] = nodeNum;
	int maxdiff = (int)log2(height);
	
	for (int i = 0; i <= maxdiff; i++) {
		parents[nodeNum][i] = temp[height - (int)pow(2, i)];
	}

	for (list<int>::iterator iter = graph[nodeNum].begin(); iter != graph[nodeNum].end(); iter++) {
		
		if (*iter == parents[nodeNum][0]) continue;
		DFS_Topar(*iter, height + 1);
	}

	temp[height] = 0;
}

void graphInput() {
	scanf("%d", &n);
	int a, b;
	for (int _ = 0; _ < n-1; _++) {
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

void matchHeight() {
	int heightDiff, maxChange;
	while (heights[left] != heights[right]) {
		heightDiff = (int)abs(heights[left] - heights[right]);
		maxChange = (int)log2(heightDiff);
		

		if (heights[left] > heights[right]) left = parents[left][maxChange];
		if (heights[left] < heights[right]) right = parents[right][maxChange];
	}
}

void biSearch(int height, int endHeight) {
	if (height < endHeight) return;
	else if (height == endHeight) {
		if (left == right) LCA = left;
		return;
	}
	
	int maxDiff = (int)log2(height - endHeight);
	if (height - maxDiff <= endHeight) maxDiff--;

	//printf("%d -> %d %d\n", maxDiff, parents[left][maxDiff], parents[right][maxDiff]);

	if (parents[left][maxDiff] == parents[right][maxDiff]) {
		LCA = parents[left][maxDiff];
		biSearch(height, height - pow(2, maxDiff)+1);
	}
	else {
		left = parents[left][maxDiff];
		right = parents[right][maxDiff];

		biSearch(height - (int)pow(2, maxDiff), endHeight);
	}
}


int main() {
	graphInput();
	DFS_Topar(1, 0);

	scanf("%d", &m);
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &left, &right);
		matchHeight();
		//printf("%d %d\n", left, right);
		biSearch(heights[left], 0);
		printf("%d\n", LCA);
	}
}

