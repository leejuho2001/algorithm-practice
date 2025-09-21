#define _CRT_SECURE_NO_WARNINGS

/*
	--- 16964 DFS ����� ���� ---

	idea
	�ʿ��� ���� : ������ ����, �� ������ ����
		-> �䱸 �ڷᱸ�� : �׷���(����Ʈ), ť
		-> ��� �˰��� : BFS

	��� : �湮���� SEQUENCE�� �ϳ��� ���鼭 ������.
	���۳�� -> �������
	
	�Ÿ�(���۳��) < �Ÿ�(�������) �� ���
	�Ÿ���� - ������� �� edge�� �ϳ� ã�´�. :: ����Ž�� ���

	�Ÿ�(���۳��) < �Ÿ�(�������) �� ���
	a. ���۳�忡�� �����ִ� edge�� ������ ����� Ȯ���Ѵ�.
		-> edge�� ������ 1�� �̻��� ��� False�� ��ȯ�ϸ� �ȴ�.
	
	b. ��������� �Ÿ� -1�� ������ ��Ʈ��ŷ
		�� �߿� a������ �ݺ�����.

	���ǻ���
	:: a-b ������ Ž���� �� ���
	a,b�� edge ������ ��� - �������
*/


#include<stdio.h>
#include<list>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

typedef struct edg {
	int s;
	int e;
}edge;

int n; //nodeNum
list<int> graph[100005];
edge edgelist[200010];

int nodeseq[100005];
int depth[100005];
int remainEdgeNum[100005];

stack<int> forDFS;
queue<int> forBFS;

void BFS(int s);
int CompEdge(edge a, edge b);
bool Comp(edge a, edge b);
int biSearchEdge(edge target);
bool prove();

int main() {
	scanf("%d", &n);
	int s, e;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &s, &e);
		edgelist[i - 1].s = s;
		edgelist[i - 1].e = e;
		edgelist[n + i - 2].s = e;
		edgelist[n + i - 2].e = s;
		graph[s].push_back(e);
		graph[e].push_back(s);
		remainEdgeNum[s]++;
		remainEdgeNum[e]++;
	}

	for (int i = 0; i < n;i++) {
		scanf("%d", nodeseq + i);
	}
	sort(edgelist, edgelist + (2 * n - 2), Comp);

	//ss
	//for (int i = 0; i < 2 * (n - 1); i++) {
	//	printf("edge :: %d - %d\n", edgelist[i].s, edgelist[i].e);
	//}
	//ee

	BFS(1);

	//ss
	//puts("depths");
	//for (int i = 1; i <= n;i++)printf("%d ", depth[i]);
	//puts("");
	//ee

	//ss
	//puts("nodeseq");
	//for (int i = 0; i < n; i++)printf("%d ", nodeseq[i]);
	//puts("");
	//ee

	bool res = prove();

	if (res == true) puts("1");
	else puts("0");
}


void BFS(int s) {
	depth[s] = 1;
	forBFS.push(s);
	int curr;
	while (!forBFS.empty()) {
		curr = forBFS.front();
		for (list<int>::iterator iter = graph[curr].begin(); iter != graph[curr].end(); iter++) {
			if (depth[*iter] == 0) {
				depth[*iter] = depth[curr] + 1;
				forBFS.push(*iter);
			}
		}

		forBFS.pop();
	}
} // depth ������ ���� BFS

int CompEdge(edge a, edge b) {
	if (a.s == b.s) {
		if (a.e < b.e) return -1;
		else if (a.e == b.e) return 0;
		else return 1;
	}
	if (a.s < b.s) return -1;
	else return 1;
} // ������ ũ�� -1, �����ϸ� 0, �������� ũ�� 1

bool Comp(edge a, edge b) {
	return CompEdge(a, b) == -1;
} // ���������� compare

int biSearchEdge(edge target) {
	int s = 0;
	int e = 2 * n - 3;

	int cent;

	while (e >= s) {
		cent = (s + e) / 2;
		if (CompEdge(target, edgelist[cent]) == -1) {
			e = cent - 1;
		} // target�� �� ������
		else if (CompEdge(target, edgelist[cent]) == 0) {
			return cent;
		}
		else {
			s = cent + 1;
		}
	}

	return -1;
} // �ش��ϴ� edgeã��

bool prove() {
	int seqOff = 0;
	if (nodeseq[0] != 1) return false;
	forDFS.push(1);
	while (seqOff < n-1) {
		int s = nodeseq[seqOff];
		int e = nodeseq[seqOff+1];
		//ss
		//printf(":: depth comp :: s = %d, %d| e = %d, %d\n", s, depth[s], e, depth[e]);
		//ee
		if (depth[e] <= depth[s]) {
			//ss
			//printf(":: remainEdges :: s = %d, %d| e = %d, %d\n", s, remainEdgeNum[s], e, remainEdgeNum[e]);
			//ee
			if (remainEdgeNum[s] > 0) return false;
			else {
				while (depth[forDFS.top()] >= depth[e]) {
					if (remainEdgeNum[forDFS.top()] > 0) return false;
					forDFS.pop();
				}
				if (remainEdgeNum[forDFS.top()] > 0 && biSearchEdge({ forDFS.top(),e }) != -1) {
					remainEdgeNum[forDFS.top()]--;
					remainEdgeNum[e]--;

					forDFS.push(e);
					seqOff++;
				}
				else return false;
			}
		}
		else {
			if (remainEdgeNum[s] > 0 && biSearchEdge({ s, e }) != -1) {
				remainEdgeNum[s] --;
				remainEdgeNum[e] --;
				forDFS.push(e);
				//ss
				//printf("traveled :: %d -> %d \n", s, e);
				//ee
				seqOff++;
			}

			else return false;
		}
	}
	return true;
}

