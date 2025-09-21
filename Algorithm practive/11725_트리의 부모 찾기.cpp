#define _CRT_SECURE_NO_WARNINGS

/*
	---- 11725_Ʈ���� �θ� ã�� ----

	���̵�� : BFS�� ���� Ʈ���� Ž����.
	1�� Ʈ���� ��Ʈ���� �������� ������ 1���� �ּ� �Ÿ��� 
	1���� �ּ� �Ÿ��� ã�� ���ؼ� DFS���� BFS�� �����.

	����� ���� �ִ� 100000���̱� ������ �׷����� 2���� �迭�� ǥ������ �ʰ�,
	����Ʈ�� �迭�� ���� ǥ����.

	*/


#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

list<int> graph[100050];
queue<int>forBFS;
int parent[100050];

int n;


/*
	---- graph_input ----
	:: param ::
	����.

	:: action ::
	����� �׷����� ����
	�ϳ��� ������ �ԷµǸ� ������ �� ������ �ش��ϴ� ����Ʈ�� ��� ������ ���� ������ �߰���.
*/
void graph_input() {
	for (int _ = 0; _ < n-1; _++) {
		int p, q;
		scanf("%d %d", &p, &q);

		graph[p].push_back(q);
		graph[q].push_back(p);
	}
}

/*
	---- BFS ----

	:: param ::
	int init_node : ���� ����� ��ȣ.

	:: Action ::
	�ʺ�켱Ž���� �ǽ���. parent�� �θ��尡 ��ϵ��� ���� ��� Ž��
*/

void BFS(int init_node) {
	forBFS.push(init_node);
	parent[init_node] = -1;

	while (!forBFS.empty()) {
		int current = forBFS.front();
		list<int> currentList = graph[current];
		list<int>::iterator iter = currentList.begin();
		for (iter; iter != currentList.end(); iter++) {
			if (parent[*iter] == 0) {
				parent[*iter] = current;
				forBFS.push(*iter);
			}
		}
		forBFS.pop();
	}
}

int main() {
	scanf("%d", &n);
	graph_input();
	BFS(1);

	for (int i = 2; i <= n; i++) {
		printf("%d\n", parent[i]);
	}
}