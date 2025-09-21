#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1167_트리의 지름 ----


	핵심 : 트리의 가중치는 음수가 없기 때문에, 트리의 지름은 리프노드와 리프노드의 거리다.
	-> 한 서브트리에 대한 두 리프노드와의 거리의 합의 최대가 되면 된다.

	한 서브트리에 대해서, 다음과 같은 세가지 값을 구함

	1. 왼쪽 서브노드의 최대 합 + 루프노드의 값
	2. 오른쪽 서브노드의 최대 합 + 루프노드의 값
	3. 왼쪽 서브노드의 최대 합 + 오른쪽 서브노드의 최대 합

	1, 2번은 비교하여 더 큰 값을 상위 트리에 대한 값으로 사용함.
	3번은 MAX와 비교하여 더 클시 갱신하는 용도로 사용.

	--> 루트 노드에서 각 노드로 가기 위한 길을 단 하나임. 
	:: 부모 노드로 향하는 값이 아닌, 자식 노드로 향하는 가중치 값을 해당 자식 노드의 weight 값으로 두고,
	한 트리 내에서 내려가면서 구할 수 있는 최대 합을 구하는 문제로 변경할 수 있음.


	::수정사항
	입력은 그래프에 대한 입력양식을 가짐(먼저 입력했다고 부모가 되었음을 확신할 수 없음)
	따라서, weight에 바로 저장하는 방식을 사용할 수 없음.
	graph에 도착지점을 int로 저장하는 것이 아닌, 도착지점과 거리(가중치)를 edge 자료형에 모아 저장하도록 함.

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
	위 문제에서 제시된  두 개의 정수 쌍으로 간선을 표현하는 입력을 받음.
	-1이 입력되었을 경우엔 두번째 정수를 받지 않고, 간선 입력단계를 탈출.
	그 외엔 두번째 정수(가중치)에 대한 값을 받아 간선정보 추가.

*/

void input() {
	int start, dest, w;
	for (int _ = 0; _ < n; _++) {
		scanf("%d", &start);
		while (1) { // -1이 입력된다는 특수 조건을 만족해야 다음 노드에 대한 입력으로 넘어감.
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
	weight 입력 여부를 알 수 있도록 하기 위해서
	weight  배열의 모든 값을 -1로 초기화.

*/

void init() {
	for (int i = 0; i < 100005; i++) {
		weight[i] = -1;
	}
}

/*
	____ isLeaf ----
	:: param ::
	node :: int : 리프노드인지 확인하려는 노드의 번호

	:: action ::
	해당 노드와 연결되어있는 간선의 수를 세어,
	간선의 수가 단 하나이고 루프노드가 아닐 경우 
	해당 노드는 부모 노드만 존재한다고 판단, 리프노드다(true)를 출력.
*/

bool isLeaf(int node) {
	return graph[node].size() == 1;
}

/*
	---- treeDiag ----
	:: param ::
	node :: int : 탐색을 진행할 노드의 번호
	parent :: int : 탐색을 진행할 노드의 부모의 번호

	:: action ::
	리프노드일 경우 : 해당 노드의 가중치를 반환
	아닐경우 : subtree의 가중치의 합의 최댓값 + 해당 노드의 가중치를 반환
	subtree의 가중치의 합 중 상위 두 tree의 가중치의 합이 max보다 클 경우 max를 

*/

int treeDiag(int node, int parent) {
	// node가 루트 노드라면 parent는 -1로 전달.
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