#define _CRT_SECURE_NO_WARNINGS
/*
	-----2098_외판원 순회 -----

	모든 edge의 비용이 크다 : 비용이 0일 경우 갈 수 없다.
	:: 기본 조건.


*/

#include<stdio.h>
#include<queue>
using namespace std;

int n;
int visited[18];
int graph[18][18] = {};

int MAXDist = 17000000;

void DFS(int start, int cur, int dist, int level) {
	if (dist > MAXDist) return; //branch

	if (level == n) {
		if (graph[cur][start] > 0 && dist + graph[cur][start] < MAXDist) {
			MAXDist = dist + graph[cur][start];
			return;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (graph[cur][i] > 0 && visited[i] == false) {
			visited[i] = true;
			DFS(start, i, dist + graph[cur][i], level + 1);
			visited[i] = false;
		}
	}

}// branch 과정을 더한 DFS :: 시간초과.

typedef struct _node {
	int start;
	int current;
	// 시작 지점과 현재지점

	int level;
	int visited[18];
	// 몇번째 탐색인가 + 어디를 들렀는가

	int cost;
	int lowBound;
	// 지금까지 얻은 비용 + 비용의 최솟값
}node;

struct cmp {
	bool operator()(node a, node b) {
		if (a.level == b.level) {
			return a.lowBound > b.lowBound; //lowBound는 낮을수록 앞에
		}
		else {
			return a.level < b.level; //level은 높을수록 앞에
		}
	}
};

priority_queue<node, vector<node>, cmp> forBNB;


/*
	----calLBound----
	input

	nod	:: *node :: Lower Bound의 값을 계산할 node 구조체의 주소 

	Action

	nod의 LowerBound를 계산하여 값을 저장함.
	LowerBound :: 지금까지 탐색해온 길이의 합 + 아직 탐색하지 않은 노드에 도달할 수 있는 최소거리의 합.
	여기서 최소거리는 시작노드가 어디인지는 상관없음.
*/
void calLBound(node * nod) {
	int result = nod->cost;
	nod->lowBound = 0;
	for (int i = 1; i <= n; i++) {
		if (nod->start == i|| nod->visited[i] == false) {
			int min = 99999999;
			for (int q = 1; q <= n; q++) {
				if (graph[i][q]!=0 && graph[i][q] < min) min = graph[i][q];
			}
			result += min;
		}
	}

	nod->lowBound = result;
}

// B&B 에서 어떤 값을 upper bound로 사용할 것인가?
// lowerbound를 만들어서 사용한다.
// lower bound를 통한 best 탐색을 사용함.

void BNB() {
	while (!forBNB.empty()) {
		node curr = forBNB.top();
		//printf("%d %d %d %d %d %d\n", curr.start, curr.current, curr.level, curr.cost, curr.lowBound, MAXDist);


		if (curr.lowBound >= MAXDist) {
			forBNB.pop();
			continue;
		}

		if (curr.level == n) {
			int destD = graph[curr.current][curr.start];
			if (destD != 0 && MAXDist > curr.cost + destD) {
				MAXDist = curr.cost + destD;
			}
			forBNB.pop();
			continue;
		}

		forBNB.pop();
		for (int i = 1; i <= n; i++) {
			if (graph[curr.current][i] != 0 && curr.visited[i] == false) {
				node temp = curr;

				temp.visited[i] = true;
				temp.cost += graph[curr.current][i];
				temp.current = i;
				temp.level += 1;
				calLBound(&temp);
				if(temp.lowBound < MAXDist ) forBNB.push(temp);
			}
		}
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf("%d", &graph[i][q]);
		}
	}
	node start = { 1, 1, 1, {}, 0, 0 };
	start.visited[1] = true;
	forBNB.push(start);
	BNB();
	printf("%d", MAXDist);
}
