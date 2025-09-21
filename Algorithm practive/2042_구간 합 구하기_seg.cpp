#define _CRT_SECURE_NO_WARNINGS

/*
	2042_���� �� ���ϱ� _ seg

	:: ���׸�Ʈ Ʈ���� ����ϴ� ����.
	���׸�Ʈ Ʈ���� index�� ã�ư��� �������� �������� ������ ������.
	���� ���׸�Ʈ Ʈ���� Index�� �ִ� ���� ������ ������ �հ� ����.

	�������:
	3���� �ٲ� ���, 3�� ����(3���� 3����)�� ������ �� ���� �鷯�ִ� ��� ����� ����
	�ش� ������ ��ȭ�� ���� ����ŭ �����ָ� ��./

	ex ) 7�̾��� 3�� ���� 4�� �ٲ۴ٸ�, �ش� �������� �����ϴ� ��� ������ ���� 3 ����.
*/

#include<stdio.h>

int nums[1000005];
int segTree[2100000];

void buildSegTree(int index, int start, int end) {
	if (start > end) return;
	if (start == end) {
		segTree[index] = nums[start];
		return;
	}

	int center = (start + end) / 2;
	buildSegTree(index * 2, start, center);
	buildSegTree(index * 2 + 1, center + 1, end);

	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

void fixSegTree(int index, int start, int end, int idx, int value) {
	int delta = value - nums[idx];
	nums[idx] = value;
	if (idx >= start && idx <= end) segTree[index] += delta;
	else return;
}

int getPartSum(int index, int start, int end, int left, int right) {
	if (start > end) return 0;
	if (left > end || right < start) return 0;
	if (start >= left && end <= right) return segTree[index];

	int center = (start + end) / 2;
	return getPartSum(index * 2, start, center, left, right) + getPartSum(index * 2 + 1, center + 1, end, left, right);
}

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d", nums + i );
	
	buildSegTree(1, 1, n);
}