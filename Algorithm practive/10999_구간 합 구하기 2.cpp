#define _CRT_SECURE_NO_WARNINGS

/*
	---- 10999_구간 합 구하기 2 ----

	하나의 숫자 변화와 구간의 크기를 통해 segment tree의 노드 값의 변화를
	예측하여 사용 -> 시간초과
	::-> 매우 넓은 범위에 대해 값을 변화시킬 경우, 거의 모든 노드에 대해 탐색을 시행하기 때문인 것으로 보임.

	따라서, lazy segment tree를 사용해주어야함.

	1. 기본적인 골자는 위에서 언습한 숫자 변화와 구간의 크기를 통해 구하는 것과 동일함.
	2. 노드의 구간이 변화시키고자 하는 숫자의 범위에 포함될 경우, 따로 존재하는 lazy 항목에 더해주는 방식을 사용함.
	3. 이후 구간합을 사용해야 할 경우 lazy를 뒤에 계산해줌. 
		lazy엔 숫자의 변화량(delta) 값이 저장되며, lazy를 계산해줄 땐 해당 노드의 lazy를 노드값에 편입시켜 준 뒤, 자식노드들의 lazy에 기존 lazy의 값을 더하는
		방식을 사용함.


	값의 절댓값의 크기가 2^63보다 작으나, 위의 계산 과정에서 오버플로우가 발생할 수 있음.
	따라서 long long int값 두 개로 이루어진 계산을 위한 자료형을 사용함.
	답은 long long int 범위 내에 존재하기 때문에, 따로 출력을 구현할 필요는 없음
*/
#include<stdio.h>
long long int pivot = 1e18;

typedef struct _loong {
	long long int over;
	long long int under;
}loong;

loong numbers[100005];
loong seg_tree[2100000];
loong lazy[2100000];

void lngInit(loong* l, int value) {
	l->over = value / pivot;
	l->under = value % pivot;
}

void lngSum(loong* l, const loong a, const loong b) {
	int carry = 0;
	l->under = (a.under + b.under) % pivot;
	l->over = (a.over + b.over) % pivot + (a.under + b.under) / pivot;
}

void lngDiff(loong* l, const loong a, const loong b) {
	return lngSum(l, a, { -b.over, -b.under });
}

long long int returnLong(const loong l) {
	return l.over * pivot + l.under;
}

void build_segtree(int index, int s, int e) {

	if (s > e) return;

	if (s == e) {
		seg_tree[index] = numbers[s]; return;
	}
	int center = (s + e) / 2;
	build_segtree(index, s, center);
	build_segtree(index, center+1, e);

	lngSum(seg_tree+index, seg_tree[index * 2], seg_tree[index * 2 + 1]);

}

void fix_segtree(int index, int s, int e, int left, int right, loong value) {

	if (s > e || e<left || s>right) return;

	else if (s >= left && e <= right) {
		lazy[index] = value;
		return;
	}



}


int main() {
	
}