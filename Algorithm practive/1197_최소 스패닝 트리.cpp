#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1197_�ּ� ���д� Ʈ�� ----
	���� �˰����� �����.
	1. �ϳ��� ��忡������ ������
	2. ������ �ִ� ���� �� ���Ե� ��尡 �ƴ� ���� ����� �ּ� ���� ����.


	-> ����� ���� ���� : ���Ḯ��Ʈ�� �迭 ���·� �׷����� ǥ��.
	::: ��� --> �ð��ʰ�.
	*/

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int v, E;

typedef struct _dege {
	int dest;
	int weight;
}edge;

struct cmp {
	bool operator()(edge a, edge b) {
		return a.weight > b.weight;
	}
};

list<edge>graph[10003];
list<int> included;
bool checked[10003];

int vertexCnt = 0;
long long int edgeSum = 0;

/*
	---- input ----
	:: Action ::
	���� �� E ��ŭ ������ �Է¹���.
	���� �׷����� �ƴϹǷ�, s�� e ��ο� �ݴ� ��ȣ�� destination�����ϴ� edge ������ ����.
*/
void input() {
	
	for (int _ = 0; _ < E; _++) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		graph[s].push_back({ e, w });
		graph[e].push_back({ s, w });
	}
}

/*
	---- prim ----

	:: Action ::
	1�� ���� ���� �Ͽ� ���� �˰����� �ǽ���.
*/


void prim() {
	included.push_back(1);
	checked[1] = true;
	vertexCnt++;

	while (vertexCnt < v) {
		int edgeLen = 12345678;
		int destination = -1;
		for (list<int>::iterator node = included.begin(); node != included.end(); node++) {
			for (list<edge>::iterator edg = graph[*node].begin(); edg != graph[*node].end(); edg++) {
				if (checked[edg->dest] == false && edg->weight < edgeLen) {
					edgeLen = edg->weight;
					destination = edg->dest;
				}
			}
		}

		if (destination == -1) break;
		else {
			//printf("%d %d\n", destination, edgeLen);

			edgeSum += (long long int)edgeLen;
			included.push_back(destination);
			checked[destination] = true;
			vertexCnt++;
		}
	}
}




int main() {
	scanf("%d %d", &v, &E);
	input();
	prim();
	if (vertexCnt < v) printf("-1");
	else printf("%lld", edgeSum);
}