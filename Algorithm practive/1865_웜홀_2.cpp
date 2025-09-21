#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1865_��Ȧ_2 ----

	������ : N-1��°���� �ݺ����� ��, ��� �Ÿ��� �ּҰ� �ǹǷ�, n��° �ݺ����� 1�� ����� �Ÿ��� �� �� �ְԵ�.

	:: �� �������� ����� �Ͽ��� �ð������� �ϱ� �����Ͽ� �ٽ� ����� �Ͽ��� ��ġ�� ���ƿ��� ��
	--> ��������� �������� ���� :: ������ �������� ����ؼ� ���ƿ����� ������ �� �� �ִ°�?
	---> ���� ����Ŭ�� ������ ��� YES, ���� ����Ŭ�� �������� ���� ��� NO.

	����, ������ ���� ������ �޶���.
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
	grph�迭�� ��� ���Ҹ� INF�� ����.
*/

void graphInit() {
	for (int i = 0; i < 510; i++) {
		for (int q = 0; q < 510; q++) graph[i][q] = INF;
	}
}


/*
	----Init----

	:: action ::
	graph ���� ����-���� �˰��� �ʿ��� ��� �迭�� �ʱ�ȭ
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

	���� : M��ŭ ��� �Է�, W��ŭ ��Ȧ �Է��� ����.
	��� �Է� : ������� ������ ��ŭ, pq�� qp ��� ������ ����.
	��Ȧ �Է� : �ܹ����̹Ƿ�, pq���⸸ ����.

	-> ����ġ�� ���� ���� �游 ��Ͽ� ����.
	== ����� ��� : �ð��� ���� ���� ������.
	== ��Ȧ�� ��� : �ð��� ���� ���� �ǵ��ư�.
*/

void Input() {
	// ��� ��Ʈ input
	for (int _ = 0; _ < M; _++) {
		int p, q, r;
		scanf("%d %d %d", &p, &q, &r);
		if (graph[p][q] > r) graph[p][q] = r;
		if (graph[q][p] > r) graph[q][p] = r;
	}
	// ��Ȧ ��Ʈ input
	for (int _ = 0; _ < W; _++) {
		int p, q, r;
		scanf("%d %d %d", &p, &q, &r);
		if (graph[p][q] > -r) graph[p][q] = -r;
	}
}

/*
	----edgesInit----

	:: param ::
	edges : list<edge> :: edge�� ���� ���� ����Ʈ

	���� : graph �迭�� ����Ǿ� �ִ� �������� ������ ������.
	���� ��� > ���� ��尡 ū ������� ������ ������ �߰�.
	���� ������ ����� ����Ʈ�� ���, ����Ʈ ���� ��� ���Ҹ� ������ �� ������ ������ �߰�.

	�Էµ� ����Ʈ�� ����-���� �˰��� ����.
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
	node_num : int :: ����-���� �˰����� ������ �׷����� ����� ��. n-1ȸ �ݺ��ؾ� ��.
	edges : list<edge> :: ����-���� �˰����� ������ �׷����� ���� ������ ������ ����Ʈ

	:: action :: ����-���� �˰����� ������.
	�ּ� �Ÿ� ���� ��Ʈ�� ���� ����Ŭ ���� ���� �Ǵ� ��Ʈ�� �̷���� ����.
	�ּ� �Ÿ� ���� : ��� ��带 ���ƺ��� dist���� ���� �Ÿ��� ������ ����
	���� ����Ŭ ���� ���� �Ǵ� : � ��尡 ���� ����Ŭ�� ���ϴ��� �Ǵ���.
	���� ����Ŭ�� ���� ���, mCycle�� �ش� ��� ���� true�� �����Ͽ� ǥ����.

	���� ���� ����Ŭ�� �� ã���� ��� �ٷ� �ش� ��Ʈ�� ������.

	:: return ::
	���� ����Ŭ�� ���� ���θ� ������.
*/
bool Bellman_Ford(int node_num, list<edge>edges) {
	// �ּ� �Ÿ� ���� ��Ʈ
	for (int i = 1; i < node_num; i++) {
		for (list<edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
			edge current = *iter;
			if (dist[current.destination] > dist[current.start] + current.weight)
				dist[current.destination] = dist[current.start] + current.weight;
		}
	}

	// ���� ����Ŭ ���� �Ǵ� ��Ʈ
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