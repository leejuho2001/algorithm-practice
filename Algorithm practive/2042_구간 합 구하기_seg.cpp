#define _CRT_SECURE_NO_WARNINGS

/*
	2042_구간 합 구하기 _ seg

	:: 세그먼트 트리를 사용하는 버전.
	세그먼트 트리의 index를 찾아가는 과정에서 구간합의 구간이 정해짐.
	따라서 세그먼트 트리의 Index에 있는 값은 정해진 구간의 합과 같음.

	수정방법:
	3번을 바꿀 경우, 3번 구간(3부터 3까지)에 도달할 때 까지 들러주는 모든 노드의 값을
	해당 구간의 변화에 대한 값만큼 더해주면 됨./

	ex ) 7이었던 3번 값을 4로 바꾼다면, 해당 구간까지 도달하는 모든 노드들의 값을 3 빼줌.
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