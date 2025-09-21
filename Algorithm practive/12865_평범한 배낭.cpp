#define _CRT_SECURE_NO_WARNINGS

/*
	---- ����� �賶 ----

	B&B �˰����� ����Ѵ�.
	B#B : BFS�� ���̽��� �ϸ�, Bound ���� ���� �ش� ��θ� pruning��.

	Bound�� ��� ��� : ������� ��� + ���Դ� ��ġ�� ���� ������ ����.
	�������� ���� ��� ���Է� ������ ������.

	--> �ð��ʰ�
	�ܼ� BFS������� ���� :: �ð��ʰ��� �߻���
	�ذ� :: priority queue�� ����ϴ� queue�� ���¸� ��ȭ��Ŵ
	������ 
	1. ���ݱ����� value�� ū ������� 
	2. remain�� ū �������
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
	int value;	// ���ݱ����� value�� ����?
	int level;	//���° �׸��� �����ΰ�
}info;

typedef struct _node {
	info info;
	float bound;	// ���� bound ����?
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
	:: bound���� �����.
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