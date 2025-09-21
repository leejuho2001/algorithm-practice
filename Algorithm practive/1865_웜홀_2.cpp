#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1865_웜홀_2 ----

	변경점 : N-1번째까지 반복했을 때, 모든 거리가 최소가 되므로, n번째 반복에선 1번 노드의 거리를 알 수 있게됨.

	:: 한 지점에서 출발을 하여서 시간여행을 하기 시작하여 다시 출발을 하였던 위치로 돌아왔을 때
	--> 출발지점이 정해지지 않음 :: 임의의 지점에서 출발해서 돌아왔을때 음수가 될 수 있는가?
	---> 음수 사이클이 존재할 경우 YES, 음수 사이클이 존재하지 않을 경우 NO.

	따라서, 정답을 내는 기준이 달라짐.
*/

#include<stdio.h>
#include<list>
using namespace std;
#define INF 12345678;

typedef struct _edge {
	int start;
	int destination;
	int weight;
}edge;

int graph[510][510];
int dist[510];
bool mCycle[510];
int TC;
int N, M, W;

//list<edge> Edges;



/*
	----graphInit----

	:: action ::
	grph배열의 모든 원소를 INF로 만듬.
*/

void graphInit() {
	for (int i = 0; i < 510; i++) {
		for (int q = 0; q < 510; q++) graph[i][q] = INF;
	}
}


/*
	----Init----

	:: action ::
	graph 포함 벨만-포드 알고리즘에 필요한 모든 배열을 초기화
*/

void Init() {
	graphInit();
	dist[1] = 0;
	mCycle[1] = false;
	for (int i = 2; i < 510; i++) {
		mCycle[i] = false;
		dist[i] = INF;
	}
}

/*
	----input----

	역할 : M만큼 경로 입력, W만큼 웜홀 입력을 받음.
	경로 입력 : 양방향이 가능한 만큼, pq와 qp 모두 조건을 따짐.
	웜홀 입력 : 단방향이므로, pq방향만 따짐.

	-> 가중치가 가장 작은 길만 기록에 남김.
	== 경로의 경우 : 시간이 가장 적게 지나감.
	== 웜홀의 경우 : 시간이 가장 많이 되돌아감.
*/

void Input() {
	// 경로 파트 input
	for (int _ = 0; _ < M; _++) {
		int p, q, r;
		scanf("%d %d %d", &p, &q, &r);
		if (graph[p][q] > r) graph[p][q] = r;
		if (graph[q][p] > r) graph[q][p] = r;
	}
	// 웜홀 파트 input
	for (int _ = 0; _ < W; _++) {
		int p, q, r;
		scanf("%d %d %d", &p, &q, &r);
		if (graph[p][q] > -r) graph[p][q] = -r;
	}
}

/*
	----edgesInit----

	:: param ::
	edges : list<edge> :: edge의 값을 넣을 리스트

	역할 : graph 배열에 저장되어 있는 간선들의 정보를 저장함.
	시작 노드 > 도착 노드가 큰 순서대로 간선의 정보를 추가.
	만약 이전에 사용한 리스트일 경우, 리스트 내의 모든 원소를 삭제한 뒤 간선의 정보를 추가.

	입력된 리스트는 벨만-포드 알고리즘에 사용됨.
*/
void edgesInit(list<edge>* edges) {
	while (!edges->empty()) edges->pop_front();

	for (int i = 1; i <= N; i++) {
		for (int q = 1; q <= N; q++) {
			if (graph[i][q] != 12345678) {
				edges->push_back({ i, q, graph[i][q] });
			}
		}
	}
}

/*
	----Bellman_Ford----

	:: param ::
	node_num : int :: 벨만-포드 알고리즘을 수행할 그래프의 노드의 수. n-1회 반복해야 함.
	edges : list<edge> :: 벨만-포드 알고리즘을 수행할 그래프의 간선 정보를 저장한 리스트

	:: action :: 벨만-포드 알고리즘을 수행함.
	최소 거리 갱신 파트와 음수 사이클 존재 여부 판단 파트로 이루어져 있음.
	최소 거리 갱신 : 모든 노드를 돌아보며 dist보다 작은 거리가 나오면 갱신
	음수 사이클 존재 여부 판단 : 어떤 노드가 음수 사이클에 속하는지 판단함.
	음수 사이클에 속할 경우, mCycle의 해당 노드 값을 true로 설정하여 표시함.

	만약 음수 사이클을 다 찾았을 경우 바로 해당 파트를 종료함.

	:: return ::
	음수 사이클의 존재 여부를 리턴함.
*/
bool Bellman_Ford(int node_num, list<edge>edges) {
	// 최소 거리 갱신 파트
	for (int i = 1; i < node_num; i++) {
		for (list<edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
			edge current = *iter;
			if (dist[current.destination] > dist[current.start] + current.weight)
				dist[current.destination] = dist[current.start] + current.weight;
		}
	}

	// 음수 사이클 여부 판단 파트
	int cnt = 0;

	for (list<edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
		edge current = *iter;
		if (dist[current.destination] > dist[current.start] + current.weight) {
			dist[current.destination] = dist[current.start] + current.weight;
			cnt++;
		}
	}

	return cnt > 0;
}

int main() {
	scanf("%d", &TC);

	for (int _ = 0; _ < TC; _++) {
		scanf("%d %d %d", &N, &M, &W);
		Init();
		Input();
		/*
		for (int i = 1; i <= N; i++) {
			for (int q = 1; q <= N; q++) {
				if (graph[i][q] == 12345678) printf("0 ");
				else printf("%d ", graph[i][q]);
			}
			puts("");
		}
		*/

		list<edge> edges;
		edgesInit(&edges);
		
		bool result = Bellman_Ford(N, edges);



		if (dist[1] < 0 || result == true) puts("YES");
		else puts("NO");
	}


}