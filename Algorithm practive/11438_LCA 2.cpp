#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11438_LCA2 ----
	트리 : 계층관계를 가지고 있음.
	+ 문제 조건 : 1번 노드가 루트노드라고 주어짐.

	-> 따라서 탐색 1회(BFS)를 통해 각 노드들간의 계층관계를 알 수 있음.
	따라서, parent() 노드를 통해서 해당 번호 노드의 부모노드가 몇인지를 저장할 수 있다.
	
	공통조상 탐색 방법
	1. level이 더 큰 노드를 가리키고 있는 포인터를 그 노드의 부모로 옮긴다.
	2. level이 같은경우, 같은 노드를 가리키는지 확인하고 그렇지 않을경우 함수 기준 왼쪽 노드를 먼저 탐색한다.
	3. 같은 노드를 가리키면 return한다.

	#시간초과.
	이진트리의 형태가 아님, 균형트리의 형태가 아니므로 공통 조상 탐색 과정에서 O(logN)을 보장할 수 없음.
	----- idea1.


	해당 문제의 해결을 위해, 무조건 log n의 복잡도를 가지는 알고리즘을 사용해야함.
	-> 높이에 대한 이분탐색의 형태를 사용할 수 있음.

	이분 탐색을 하기 위해, 트리에 DT를 사용함 (DFS를 통해 2^n번째 조상을 알 수 있음.

	이분탐색 방식 :
	-> 원하는 범위 내에서 최대 크기의 2^n을 기준으로 하는 이분탐색을 사용함.


	순서 :
	더 높은 높이에 있는 노드를 낮은 높이에 있는 노드와 맞추기 ( 여기서도 최대 2^n)을 사용함.

	그리고 LCA를 깊이에 대한 이분탐색으로 찾음.

	DFS에선 어떻게 조상노드를 찾는가?
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
// tree build용 BFS

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
// height : 해당 노드의 깊이를 반환.
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

