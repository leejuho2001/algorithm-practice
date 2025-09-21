#define _CRT_SECURE_NO_WARNINGS
/*
---- - 2098_���ǿ� ��ȸ---- 

	��� edge�� ����� ũ�� : ����� 0�� ��� �� �� ����.
	::�⺻ ����.

	DT �� ���� ���� ª�� ������ �κп� ���� ����� �Ѵ�.
	DT�� 2 ���� �κ����� ������.
	bitmask : ���ݱ��� �湮�� ���� 1, �湮���� �������� 0���� ǥ���� �������� �������� �ٲ� ���.
	current : ���������� �湮�� ��

	�� �� ������ �����ϴ� �湮����� ���ų�, �ش� �湮��Ϻ��� �� ������ ���� ��� �ش� ��쿡 ���� Ž���� �����Ѵ�.

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
