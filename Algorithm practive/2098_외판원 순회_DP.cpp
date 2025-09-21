#define _CRT_SECURE_NO_WARNINGS
/*
---- - 2098_외판원 순회---- 

	모든 edge의 비용이 크다 : 비용이 0일 경우 갈 수 없다.
	::기본 조건.

	DT 를 통해 가장 짧게 도착한 부분에 대한 기록을 한다.
	DT는 2 개의 부분으로 나뉜다.
	bitmask : 지금까지 방문한 곳을 1, 방문하지 않은곳을 0으로 표시한 이진수를 십진수로 바꿔 기록.
	current : 마지막으로 방문한 곳

	이 두 가지를 만족하는 방문기록이 없거나, 해당 방문기록보다 더 가격이 낮은 경우 해당 경우에 대한 탐색을 시행한다.

*/

#include<stdio.h>
#include<queue>
using namespace std;

typedef struct _node {
	int bitmask;
	int current;
}node;

int n;
int graph[17][18];
int visited[67000][17];

int pow2(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) res *= 2;

	return res;
}

void push(queue<node> &q, node curr, int dest) {
	int current = curr.current;
	int bitm = curr.bitmask;
	
	int destBM = bitm + pow2(dest - 1);
	//printf("push %d %d - %d to %d\n", curr.current, dest, bitm, destBM);
	bool cond1 = graph[current][dest] != 0;
	bool cond2 = graph[current][dest] + visited[bitm][current] < visited[destBM][dest];
	bool cond3 = visited[destBM][dest] == 0;
	if (cond1 && (cond2||cond3)) {
		visited[destBM][dest] = visited[bitm][current] + graph[current][dest];
		q.push({ destBM, dest});
		//printf("checked %d  to %d %d\n", visited[destBM][dest], destBM, dest);
	}
}

void BFS() {
	queue<node> forbfs = {};
	for (int i = 1; i <= n; i++) {
		forbfs.push({1, 1});
	}

	while (!forbfs.empty()) {
		node curr = forbfs.front();
		//printf("%d %d\n", curr.current, curr.bitmask);
		int temp = curr.bitmask;
		for (int i = 1; i <= n; i++) {
			
			int v = temp % 2;
			temp /= 2;
			if (v == 0) { 
				push(forbfs, curr, i); 
			}

		}
		forbfs.pop();
	}
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf("%d", &graph[i][q]);
		}
	}

	BFS();
	

	int min = 123456789;
	for (int i = 1; i <= n; i++) {
		int val = visited[pow2(n) - 1][i];
		if (val!=0 && graph[i][1] != 0 && min > val + graph[i][1])
			min = visited[pow2(n) - 1][i] + graph[i][1];
	}

	for (int i = 1; i <= pow2(n) - 1; i++) {
		for (int q = 1; q <= n; q++) {
			//printf("%d ", visited[i][q]);
		}
		//puts("");
	}

	printf("%d", min);
}
