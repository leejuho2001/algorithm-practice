#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2252_�� ����� ----

	���� ����� :: �� �Ʒ��� �����Ѵ� :: Ʈ�� ���¸� ������.
	Ʈ�� ���¸� ���� ��, Ž����Ű�� �ȴ�.
	Ʈ���� �������� �ʴ� ���, ���� ��ġ�ϴ��� ����� ����.

	Ʈ���� ����� �� :
	�ִ� �Ÿ��� ��� �����.
	�׷����� ���� �׷����� ����Ѵ�.

	���������� ��Ʈ��带 ã�� ��, ��ȸ�ϴ� ����� ����Ѵ�.

*/

#include<stdio.h>
#include<list>
using namespace std;
typedef struct _node {
	int key;
	int edgeCnt;
}node;

int n, m;
list<int>graph[32005];
int nearest[32005];
node edgeCnts[32005];

void make_tree() {

}

void graphinput() {
	int back, front;
	for (int _ = 0; _ < m; _++) {
		scanf("%d%d", &back, &front);

		graph[front].push_back(back);
		edgeCnts[front].edgeCnt++;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i<= n; i++) {
		edgeCnts[i].key = i;
	}
	graphinput();

}