#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1761_정점들의 거리 ----

	트리에서 두 노드의 거리 = 두 노드의 LCA를 찾은 다음, A의 LCA 까지의 거리 + B의 LCA 까지의 거리.
	따라서, LCA 알고리즘을 거리에도 적용시킬 수 있으면 된다.

	어떻게 거리에 적용시키는가?
	LCA에서 조상노드는 2^n의 형태로 저장된다.
	
	한 노드에서 2^n개의 조상이 있다면,
	그 위의 2^(n-1)번째 조상노드는 2^(n-1)개의 조상노드를 가진다.

	따라서, dist[n] = dist[curr][n-1] + dist[ancestor[curr][n-1]][n-1];
	이를 이용하면, 거리 또한 logn의 복잡도로 구할 수 있게 된다.
*/

#include<stdio.h>
#include<math.h>
#include<list>

using namespace std;

typedef struct _node {
	int node;
	int dist;
}node;

list<node>graph[40005];
int ancestor[40005][16];
int dist[40005][16];
int height[40005];
int temp[40005];
int n, m;

int left, right, LCA;
int lll, rrr, dst;
void DFS_forAD(int nodeNum, int Height) {
	height[nodeNum] = Height;
	temp[Height] = nodeNum;
	int maxDef = (int)log2(Height);
	
	for (int i = 0; i <= maxDef; i++) {
		ancestor[nodeNum][i] = temp[Height - (int)pow(2, i)];
		if (i > 0) dist[nodeNum][i] = dist[nodeNum][i - 1] + dist[ancestor[nodeNum][i - 1]][i - 1];
	}

	for (list<node>::iterator iter = graph[nodeNum].begin(); iter != graph[nodeNum].end(); iter++) {
		if (iter->node == ancestor[nodeNum][0]) continue;
		else {
			dist[iter->node][0] = iter->dist;
			DFS_forAD(iter->node, Height + 1);
		}
	}

	temp[Height] = 0;
}

void graphInit() {
	scanf("%d", &n);
	int a, b, w;
	for (int _ = 1; _ < n; _++) {
		scanf("%d %d %d", &a, &b, &w);
		graph[a].push_back({ b,w });
		graph[b].push_back({ a,w });
	}
}

void matchHeight() {
	
	int heightDiff, maxChange;
	while (height[left] != height[right]) {
		//printf("mh. %d %d\n", left, right);
		heightDiff = (int)abs(height[left] - height[right]);
		maxChange = (int)log2(heightDiff);


		if (height[left] > height[right]) left = ancestor[left][maxChange];
		if (height[left] < height[right]) right = ancestor[right][maxChange];
	}
}

void biSearch(int Height, int endHeight) {
	//printf("bs. %d %d\n", Height, endHeight);
	if (Height < endHeight) return;
	else if (Height == endHeight) {
		if (left == right) LCA = left;
		return;
	}

	int maxDiff = (int)log2(Height - endHeight);
	if (Height - maxDiff <= endHeight) maxDiff--;

	//printf("%d -> %d %d\n", maxDiff, parents[left][maxDiff], parents[right][maxDiff]);

	if (ancestor[left][maxDiff] == ancestor[right][maxDiff]) {
		LCA = ancestor[left][maxDiff];
		biSearch(Height, Height - pow(2, maxDiff) + 1);
	}
	else {
		left = ancestor[left][maxDiff];
		right = ancestor[right][maxDiff];

		biSearch(Height - (int)pow(2, maxDiff), endHeight);
	}
}

void addDistance(int target) {
	bool flag = false;
	int maxdif;
	while (height[left] > height[target]) {
		//printf("l %d\n", left);
		maxdif = (int)log2(height[left] - height[target]);
		dst += dist[left][maxdif];
		left = ancestor[left][maxdif];
	}

	while (height[right] > height[target]) {
		//printf("r %d\n", right);
		maxdif = (int)log2(height[right] - height[target]);
		dst += dist[right][maxdif];
		right = ancestor[right][maxdif];
	}
}

int main() {
	graphInit();
	DFS_forAD(1, 0);
	scanf("%d", &m);
	for (int _ = 0; _ < m; _++) {
		dst = 0;
		LCA = 0;
		scanf("%d %d", &lll, &rrr);
		left = lll, right = rrr;
		matchHeight();
		biSearch(height[left], 0);
		left = lll, right = rrr;
		addDistance(LCA);

		printf("%d\n", dst);
	}
	
}