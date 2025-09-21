#define _CRT_SECURE_NO_WARNINGS

/*
	---- 평범한 배낭 ----

	B&B 알고리즘을 사용한다.
	B#B : BFS를 베이스로 하며, Bound 값에 따라서 해당 경로를 pruning함.

	Bound값 계산 방식 : 현재까지 결과 + 무게당 가치가 높은 순서로 더함.
	무게합이 넘을 경우 무게로 나누어 구해줌.

	--> 시간초과
	단순 BFS방식으로 구현 :: 시간초과가 발생함
	해결 :: priority queue로 사용하는 queue의 형태를 변화시킴
	비교조건 
	1. 지금까지의 value가 큰 순서대로 
	2. remain이 큰 순서대로
*/


#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;

int n, w, v, k;
typedef struct _item {
	int weight;
	int value;
}item;

typedef struct _info {
	int remain; // 
	int value;	// 지금까지의 value의 합은?
	int level;	//몇번째 항목을 볼것인가
}info;

typedef struct _node {
	info info;
	float bound;	// 현재 bound 값은?
}node;



struct nodeCmp {
	bool operator()(node a, node b) {
		return a.bound < b.bound;
	}
};

bool itemCmp(item a, item b) {
	float valA = (float)a.value / a.weight;
	float valB = (float)b.value / b.weight;
	return valA > valB;
}

item items[105];
priority_queue<node, vector<node>, nodeCmp> forBFS;

int MAX = 0;

/*
	---- get_bound ----
	:: params ::

	
	:: Action ::
	:: bound값을 계산함.
*/
float get_bound(info _info) {
	int value = _info.value;
	int start = _info.level;
	int remain = _info.remain;
	
	float result = (float) value;
	for (int i = start; i < n; i++) {
		
		if (remain >= items[i].weight) {
			remain -= items[i].weight;
			result += items[i].value;
		}
		else {
			result += (float)(items[i].value * remain) / items[i].weight;
			remain = 0;
		}
	}
	return result;
}

void infoPrint(node curr) {
	printf("%d %d %d\n", curr.info.value, curr.info.remain, curr.info.level);
}

node makeNode(int valA, int valB, int valC) {
	return { {valA, valB, valC }, get_bound({valA, valB, valC }) };
}

/*
	---- BranchAndBound ----
*/

void BranchAndBound() {
	forBFS.push(makeNode(k, 0, 0));

	while (!forBFS.empty()) {
		node top = forBFS.top();
		//infoPrint(top);

		info current = top.info;

		if (current.value > MAX) MAX = current.value ;

		if (top.bound <= MAX || current.level >= n) {
			forBFS.pop();
			continue;
		}

		int itemW = items[current.level].weight;
		int itemV = items[current.level].value;

		if (current.remain >= itemW) {
			forBFS.push( makeNode(current.remain - itemW, current.value + itemV, current.level + 1));
		}
		forBFS.push(makeNode( current.remain, current.value, current.level + 1 ));
		forBFS.pop();
	}
}





int main() {
	
	
	
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		int tempw, tempv;
		scanf("%d%d", &items[i].weight, &items[i].value);
	}
	sort(items, items + n, itemCmp);

	BranchAndBound();
	printf("%d", MAX);

}