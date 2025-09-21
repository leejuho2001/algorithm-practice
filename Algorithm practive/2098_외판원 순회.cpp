#define _CRT_SECURE_NO_WARNINGS
/*
	-----2098_���ǿ� ��ȸ -----

	��� edge�� ����� ũ�� : ����� 0�� ��� �� �� ����.
	:: �⺻ ����.


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

}// branch ������ ���� DFS :: �ð��ʰ�.

typedef struct _node {
	int start;
	int current;
	// ���� ������ ��������

	int level;
	int visited[18];
	// ���° Ž���ΰ� + ��� �鷶�°�

	int cost;
	int lowBound;
	// ���ݱ��� ���� ��� + ����� �ּڰ�
}node;

struct cmp {
	bool operator()(node a, node b) {
		if (a.level == b.level) {
			return a.lowBound > b.lowBound; //lowBound�� �������� �տ�
		}
		else {
			return a.level < b.level; //level�� �������� �տ�
		}
	}
};

priority_queue<node, vector<node>, cmp> forBNB;


/*
	----calLBound----
	input

	nod	:: *node :: Lower Bound�� ���� ����� node ����ü�� �ּ� 

	Action

	nod�� LowerBound�� ����Ͽ� ���� ������.
	LowerBound :: ���ݱ��� Ž���ؿ� ������ �� + ���� Ž������ ���� ��忡 ������ �� �ִ� �ּҰŸ��� ��.
	���⼭ �ּҰŸ��� ���۳�尡 ��������� �������.
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

// B&B ���� � ���� upper bound�� ����� ���ΰ�?
// lowerbound�� ���� ����Ѵ�.
// lower bound�� ���� best Ž���� �����.

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
