#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2357_�ּڰ��� �ִ� ----
	���׸�Ʈ Ʈ���� �����
	-> ���� ���� ���, Ʈ���� ���� �ƴ� -1�� ��ȯ,
	-1�� ��ȯ�Ǿ��� ���, �ݴ��� Ʈ�� ���� ������.
	���� �ڽĳ�忡 �ش��ϴ� ������ �ִ� / �ּҰ��� �޾ƿ� ���ϸ�
	���յ� ������ �ִ�/ �ּҸ� �� �� ����.
*/

#include<stdio.h>

typedef struct _node {
	int min;
	int MAX;
}node;

int numbers[100005];
node segTree[263000];

void buildSegTree(int index, int start, int end) {
	if (start > end) return;

	if (start == end) {
		segTree[index] = { numbers[start], numbers[end] };
		return;
	}

	int leftIndex = index * 2, rightIndex = index * 2 + 1;
	int center = (start + end) / 2;
	buildSegTree(leftIndex, start, center);
	buildSegTree(rightIndex, center + 1, end);

	segTree[index].min = segTree[leftIndex].min < segTree[rightIndex].min ? segTree[leftIndex].min : segTree[rightIndex].min;
	segTree[index].MAX = segTree[leftIndex].MAX > segTree[rightIndex].MAX ? segTree[leftIndex].MAX : segTree[rightIndex].MAX;

	return;
}

node partminMAX(int index, int start, int end, int left, int right) {
	int center = (start + end) / 2;
	node result = {};

	if (right < start || left > end) { 
		//printf("%d %d - [-1, -1]\n", start, end);
		return { -1, -1 }; }
	if (start == end) { 
		//printf("%d %d - [%d, %d]\n", start, end, segTree[index].min, segTree[index].MAX);
		return segTree[index]; 
	}
	if (right >= end && left <=start) { 
		//printf("%d %d - [%d, %d]\n", start, end, segTree[index].min, segTree[index].MAX);
		return segTree[index]; 
	}


	node leftNode = partminMAX(index * 2, start, center, left, right);
	node rightNode = partminMAX(index * 2 + 1, center + 1, end, left, right);

	if (leftNode.min == -1) result.min = rightNode.min;
	else if (rightNode.min == -1) result.min = leftNode.min;
	else result.min = leftNode.min < rightNode.min ? leftNode.min : rightNode.min;

	if (leftNode.MAX == -1) result.MAX = rightNode.MAX;
	else if (rightNode.MAX == -1) result.MAX = leftNode.MAX;
	else result.MAX = leftNode.MAX > rightNode.MAX ? leftNode.MAX : rightNode.MAX;

	//printf("%d %d - [%d %d]\n", start, end, result.min, result.MAX);

	return result;
}


int main() {
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", numbers + i+1);

	buildSegTree(1, 1, n);
	//node res1 = partminMAX(1, 1, n, 2, 5);
	//node res2 = partminMAX(1, 1, n, 1, 3);
	//printf("%d %d\n", res1.min, res1.MAX);
	//printf("%d %d", res2.min, res2.MAX);

	int p, q;
	node res = {};
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &p, &q);
		res = partminMAX(1, 1, n, p, q);
		printf("%d %d\n", res.min, res.MAX);
	}
}

