#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1167_Ʈ���� ���� ----


	�ٽ� : Ʈ���� ����ġ�� ������ ���� ������, Ʈ���� ������ �������� ��������� �Ÿ���.
	-> �� ����Ʈ���� ���� �� ���������� �Ÿ��� ���� �ִ밡 �Ǹ� �ȴ�.

	�� ����Ʈ���� ���ؼ�, ������ ���� ������ ���� ����

	1. ���� �������� �ִ� �� + ��������� ��
	2. ������ �������� �ִ� �� + ��������� ��
	3. ���� �������� �ִ� �� + ������ �������� �ִ� ��

	1, 2���� ���Ͽ� �� ū ���� ���� Ʈ���� ���� ������ �����.
	3���� MAX�� ���Ͽ� �� Ŭ�� �����ϴ� �뵵�� ���.

	--> ��Ʈ ��忡�� �� ���� ���� ���� ���� �� �ϳ���. 
	:: �θ� ���� ���ϴ� ���� �ƴ�, �ڽ� ���� ���ϴ� ����ġ ���� �ش� �ڽ� ����� weight ������ �ΰ�,
	�� Ʈ�� ������ �������鼭 ���� �� �ִ� �ִ� ���� ���ϴ� ������ ������ �� ����.


	::��������
	�Է��� �׷����� ���� �Է¾���� ����(���� �Է��ߴٰ� �θ� �Ǿ����� Ȯ���� �� ����)
	����, weight�� �ٷ� �����ϴ� ����� ����� �� ����.
	graph�� ���������� int�� �����ϴ� ���� �ƴ�, ���������� �Ÿ�(����ġ)�� edge �ڷ����� ��� �����ϵ��� ��.

*/


#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

typedef struct _edge {
	int dest;
	int weight;
}edge;

int n;
list<edge>graph[100005];
int weight[100005];
int Max = 0;
bool debug = false;

struct cmp {
	bool operator()(int a, int b) {
		return a < b;
	}
};



/*
	---- input ----
	:: action ::
	�� �������� ���õ�  �� ���� ���� ������ ������ ǥ���ϴ� �Է��� ����.
	-1�� �ԷµǾ��� ��쿣 �ι�° ������ ���� �ʰ�, ���� �Է´ܰ踦 Ż��.
	�� �ܿ� �ι�° ����(����ġ)�� ���� ���� �޾� �������� �߰�.

*/

void input() {
	int start, dest, w;
	for (int _ = 0; _ < n; _++) {
		scanf("%d", &start);
		while (1) { // -1�� �Էµȴٴ� Ư�� ������ �����ؾ� ���� ��忡 ���� �Է����� �Ѿ.
			scanf("%d", &dest);
			
			if (dest == -1) break;
			else {
				scanf("%d", &w);
				graph[start].push_back({dest, w});
			}
		}
	}
}

/*
	---- init ----
	:: action ::
	weight �Է� ���θ� �� �� �ֵ��� �ϱ� ���ؼ�
	weight  �迭�� ��� ���� -1�� �ʱ�ȭ.

*/

void init() {
	for (int i = 0; i < 100005; i++) {
		weight[i] = -1;
	}
}

/*
	____ isLeaf ----
	:: param ::
	node :: int : ����������� Ȯ���Ϸ��� ����� ��ȣ

	:: action ::
	�ش� ���� ����Ǿ��ִ� ������ ���� ����,
	������ ���� �� �ϳ��̰� ������尡 �ƴ� ��� 
	�ش� ���� �θ� ��常 �����Ѵٰ� �Ǵ�, ��������(true)�� ���.
*/

bool isLeaf(int node) {
	return graph[node].size() == 1;
}

/*
	---- treeDiag ----
	:: param ::
	node :: int : Ž���� ������ ����� ��ȣ
	parent :: int : Ž���� ������ ����� �θ��� ��ȣ

	:: action ::
	��������� ��� : �ش� ����� ����ġ�� ��ȯ
	�ƴҰ�� : subtree�� ����ġ�� ���� �ִ� + �ش� ����� ����ġ�� ��ȯ
	subtree�� ����ġ�� �� �� ���� �� tree�� ����ġ�� ���� max���� Ŭ ��� max�� 

*/

int treeDiag(int node, int parent) {
	// node�� ��Ʈ ����� parent�� -1�� ����.
	if(debug == true) printf("%d %d\n", node, parent);

	if (parent != -1 && isLeaf(node) == true) return weight[node];
	else {
		if (debug == true) puts("prQ");
		priority_queue<int, vector<int>, cmp> maxHeap;

		for (list<edge>::iterator iter = graph[node].begin(); iter != graph[node].end(); iter++) {
			
			edge current = *iter;
			int destination = current.dest;


			if (destination == parent) continue;
			if (weight[destination] == -1) weight[destination] = current.weight;
			maxHeap.push(treeDiag(destination, node));
		}
		if (!maxHeap.empty()) {
			int first = maxHeap.top();
			maxHeap.pop();
			if (maxHeap.empty()) {
				if (first > Max) Max = first;
			}
			else {
				int second = maxHeap.top();
				maxHeap.pop();

				if (first + second > Max) Max = first + second;
			}
			//printf("\n=%d %d=%d==\n", node, parent, first);
			return first + weight[node];
		}
	}
}



int main() {
	//debug = true;
	scanf("%d", &n);
	init();
	input();
	/*
	for (int i = 1; i <= n; i++) {
		for (list<edge>::iterator iter = graph[i].begin(); iter != graph[i].end(); iter++) {
			printf("%d ", *iter);
		}
		puts("");
	}
	puts("--------------");
	for (int i = 1; i <= n; i++) {
		printf("%d ", weight[i]);
	}
	puts("\n--------------");
	*/

	treeDiag(1, -1);

	printf("%d", Max);
}