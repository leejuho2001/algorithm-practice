#define _CRT_SECURE_NO_WARNINGS
#define MSize 100005
#define ancestor 0
#define maximum 1
#define minimum 2

/*
	---- 3176_도로 네트워크 ----

	n개의 도시, n-개의 도로.
	유일한 다른 도시로 향하는 길
	= 사이클이 존재하지 않으며 모든 
	--> 트리임을 알 수 있음.

	트리 :: LCA를 사용하여 시간복잡도를 줄일 수 있음.

	--> LCA 를 어떤식으로 활용하는가?
	4번째 위에 있ㄴ는 트리까지 최소 길이
	 = 2번째 위의 2번째 위 조상까지의 최소와 2번째 위 조상의 2번째 위 조상까지의 최소를 비교하여 값을 정할 수 있음.

	 이를 이용할 경우, LCA를 구해두고 거기까지의 구간 중 가장 길고 짧은 거리를 구할 수 있어짐.
*/

#include<stdio.h>
#include<math.h>
#include<utility>
#include<list>
#include<queue>
using namespace std;

typedef struct _edge {
	int target;
	int weight;
}edge;

int n, m, k;
queue<pair<int, int>>problems;
list<edge> graph[MSize];
int depth[MSize];
int treeinform[MSize][17][3];

void graphinput() {
	int s, e, w;
	for (int _ = 1; _ < n; _++) {
		scanf("%d %d %d", &s, &e, &w);

		graph[s].push_back({ e, w });
		graph[e].push_back({ s, w });
	}
}

int bigger(int a, int b) {
	if (a > b) return a;
	return b;
}

int smaller(int a, int b) {
	if (a < b) return a;
	return b;
}

void DFS(int nodeNum) {
	int maxDepth = (int)log2(depth[nodeNum]);

	for (int i = 0; i < maxDepth; i++) {
		int anc = treeinform[nodeNum][i][ancestor];
		treeinform[nodeNum][i + 1][ancestor] = treeinform[anc][i][ancestor];
		treeinform[nodeNum][i + 1][maximum] = bigger(treeinform[anc][i][maximum], treeinform[nodeNum][i][maximum]);
		treeinform[nodeNum][i + 1][minimum] = smaller(treeinform[anc][i][minimum], treeinform[nodeNum][i][minimum]);
	}


	list<edge>node = graph[nodeNum];
	for (list<edge>::iterator iter = node.begin(); iter != node.end(); iter++) {
		int target = iter->target;
		int weight = iter->weight;
		if (target != treeinform[nodeNum][0][ancestor]) {
			treeinform[target][0][ancestor] = nodeNum;
			treeinform[target][0][maximum] = weight;
			treeinform[target][0][minimum] = weight;

			depth[target] = depth[nodeNum] + 1;
			DFS(target);
		}
		
	}
}

void treeDeploy() {
	int head = 1;
	for (int i = 1; i <= n; i++) {
		if (graph[i].size() > graph[head].size()) head = i;
	}
	depth[head] = 1;
	DFS(head);
}

int getLCA(int num1, int num2) {
	int curr1 = num1, curr2 = num2;

	while (depth[curr1] != depth[curr2]) {
		int def = depth[curr1] - depth[curr2]; if (def < 0) def *= -1;
		int diff = (int)log2(def); 
		if (depth[curr1] > depth[curr2]) curr1 = treeinform[curr1][diff][ancestor];
		else curr2 = treeinform[curr2][diff][ancestor];
	}
	

	while (curr1 != curr2) {
		int i = 0;
		for (i; treeinform[curr1][i][ancestor] != treeinform[curr2][i][ancestor]; i++);
		curr1 = treeinform[curr1][i][ancestor];
		curr2 = treeinform[curr2][i][ancestor];
	}

	return curr1;
}

pair<int, int> getMINMAX(int num, int anc) {
	if (num == anc) return make_pair(-1, -1);
	int diff = (int)log2(depth[num] - depth[anc]);
	
	pair<int, int> pair1 = make_pair(treeinform[num][diff][maximum], treeinform[num][diff][minimum]);
	pair<int, int> pair2 = getMINMAX(treeinform[num][diff][ancestor], anc);

	if (pair2.first == -1) return pair1;
	else return make_pair(bigger(pair1.first, pair2.first), smaller(pair1.second, pair2.second));
}

pair <int, int> getAnswer(int num1, int num2) {
	int LCA = getLCA(num1, num2);
	//printf("LCA ::: %d\n", LCA);
	pair<int, int> ans1 = getMINMAX(num1, LCA);
	pair<int, int>ans2 = getMINMAX(num2, LCA);
	int anss1, anss2;
	if (ans1.first == -1) anss1 = ans2.first;
	else if (ans2.first == -1) anss1 = ans1.first;
	else anss1 = bigger(ans1.first, ans2.first);

	if (ans1.second == -1) anss2 = ans2.second;
	else if (ans2.second == -1) anss2 = ans1.second;
	else anss2 = smaller(ans1.second, ans2.second);
	return make_pair(anss1, anss2);
}

int main() {
	
	scanf("%d", &n);
	graphinput();
	treeDeploy();
	/*printf("::: ");
	for (int i = 1; i <= n; i++) {
		printf("%d ", depth[i]);//treeinform[n][0][ancestor]);
	}puts("");
	*/
	scanf("%d", &k);
	for (int _ = 0; _ < k; _++) {
		int a, b;
		scanf("%d %d", &a, &b);

		problems.push(make_pair(a, b));
	}

	while (!problems.empty()) {
		int a = problems.front().first, b = problems.front().second;


		pair<int, int> anss = getAnswer(a, b);
		printf("%d %d\n", anss.second, anss.first);
		problems.pop();
	}
}