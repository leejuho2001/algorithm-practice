#define _CRT_SECURE_NO_WARNINGS

/*
	2252_�� �����_topol

	1. ũ�� ����� ���� �׷�����
	2. ������� ũ��� �׷����� ���ǵǴ� ���, ����Ŭ�� �߻��� �� ����.
	 :::: A>B>C>A �� �Ұ����ϱ� ����.

	---->> ���������� ����� �� �ִ�.
	==>> ���������� �� ������ �������� ���� �ڷῡ ���� Ȱ���ϱ� ����.

	
*/

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int n, m;

queue<int>forTPS;
bool visited[32050] = {};
list<int>graph[32050] = {};
int inDeg[32050] = {};


void topology_q() {
	int curr, curr2;
	while (!forTPS.empty()) {
		curr = forTPS.front();
		for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
			curr2 = *iter;
			if (visited[curr2] == false && inDeg[curr2] > 0) {
				inDeg[curr2]--;
				if (inDeg[curr2] == 0) {
					forTPS.push(curr2);
					visited[curr2] = true;
				}
			}
		}
		printf("%d ", curr);
		forTPS.pop();
	}
	
}

void graphInit() {
	int p, q;
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &p, &q);
		graph[p].push_back(q);
		inDeg[q]++;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	graphInit();
	for (int i = 1; i <= n; i++) {
		if (visited[i] == false && inDeg[i] == 0) {
			forTPS.push(i);
			visited[i] = true;
			topology_q();
		}
	}
}