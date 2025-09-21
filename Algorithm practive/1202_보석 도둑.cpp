#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1202_���� ���� ----

	��� 1. greedy alg

	���̵�� : value�� ���� ������� �����س���,
	���� ���� value�� ���� ������ ���� �� �ִ� ���� �� ���� ������ ����� �� �ִ�.

	--> �׷��� ����� ��� ������ �ִ밡 �ȴ�.

	���� : �̺�Ž���� ����� ã�� �ָӴϰ� �̹� ���� ���?
	�迭�� ����� �ؽ����̺��� ���ó�� ����ĭ���� �̷��.
	-> �� ������ �ð����⵵ O(n)�� ������ �����̱� ������, ��ü ������ n^2logn�̵ȴ�.
	�־��� ��쿡�� �ð��ʰ��� �߻��� ���ɼ��� ����.

	�ذ��� : �̸� ���׸�Ʈ Ʈ���� �ذ��Ѵ�.
	���� ������ �̷��� �ȴ�.

	1. ����Ʈ���� �� �� �ִ� �ּ�ũ���� ������ ã�´�.
	2. �� ���� ���� ���� ū ��������� �������� ������ �� �� �ִ� ���� ���� ������ ���׸�Ʈ Ʈ���� �̿��� ã�´�.
	3. �ش� ���濡 ������ ����ְ� ������ ������Ʈ�Ѵ�.


	����Ʈ���� ���°� : �ڽĳ�尡 ��� true�� : true,
	�ڽĳ�尡 false���� �ϳ��� ������, false.

	�������� �ش� ���濡 ����ִ����� �ǹ���.
	���� �ش� ���濡 ���� ��� �ش� ���������� ������ ������Ʈ��.
*/

#include<stdio.h>
#include<algorithm>
using namespace std;

typedef struct segNode {
	bool lazySolved;
	bool value;

	int s;
	int e;
};


typedef struct _jewel {
	int weight;
	int value;
}jewel;

bool jewelCmp(jewel a, jewel b) {
	return a.value > b.value;
}

segNode segTree[1050000];
int bagWeight[300050];
jewel jewels[300050];

int n, k;
long long int valSum;
int find_pos(int s, int e, int value) {
	int center = (s + e) / 2;
	//printf("find_pos :: %d %d -> %d %d\n", s, e, bagWeight[center], value);

	if (s > e) return -1;

	if (s == e) {
		if (s >= k || e < 0 || bagWeight[s] < value) return -1;
		else return s;
	}

	
	if (bagWeight[center] == value) return find_pos(s, center, value);
	else if (bagWeight[center] < value) return find_pos(center + 1, e, value);
	else return find_pos(s, center, value);
} // ������ ���� �� �ִ� ���� ���� ������ ��ġ


void lazyDeployment(int index) {
	segTree[index].lazySolved = true;
	int s = segTree[index].s;
	int e = segTree[index].e;

	int center = (s + e) / 2;

	bool sL = s == center ? true : false;
	bool eL = center + 1 == e ? true : false;

	segTree[index * 2] = {sL, 0, s, center};
	segTree[index * 2 + 1] = {eL, 0, center+1, e};
}

int find_seg_pos(int index, int point) {
	
	if (segTree[index].lazySolved == false)lazyDeployment(index);
	int s = segTree[index].s, e = segTree[index].e;
	int center = (s + e) / 2;
	//printf("%d %d :: %d %d %d\n", index, point, s, center, e);
	if (s == e) return index;
	if (point > center) return find_seg_pos(index * 2 + 1, point);
	else return find_seg_pos(index * 2, point);

}// �ش� point(���� ������ ��ġ)�� �ش��ϴ� segment tree�� index�� ��ȯ��.



int find_unUsed(int point) {
	int savedTemp = point;
	if (segTree[point].value == false) return point;

	int temp = savedTemp/2;

	while(temp > 0) {
		//printf("find unUsed :: %d\n", temp);
		if (savedTemp % 2 == 0) {
			if (segTree[temp*2+1].value == 0) break;
		}

		savedTemp = temp;
		temp = savedTemp / 2;
	}

	if (temp == 0) return -1;
	temp *= 2;
	temp += 1;

	while (segTree[temp].s != segTree[temp].e) {

		//printf("find unUsed :: %d -> left : %d, right : %d\n", temp, segTree[temp*2].value, segTree[temp*2+1].value);
		if (segTree[temp].lazySolved == false) lazyDeployment(temp);
		if (segTree[temp * 2].value == false) temp = temp * 2;
		else temp = temp * 2 + 1;
	}

	return temp;
}

void fixSegTree(int point) {
	// point�� ���� : ��Ʈ ����� �ּҿ�����.
	segTree[point].value = true;
	int temp = point / 2;

	while (temp > 0) {
		if (segTree[temp * 2].value && segTree[temp * 2 + 1].value)
			segTree[temp].value = true;
		
		temp /= 2;
	}
}


void pos() {
	for(int i=0;i<n;i++){
		//printf("%d :: ", i);
		jewel current = jewels[i];
		int position = find_pos(0, k - 1, current.weight);
		//printf("%d %d -> %d \n",current.value, current.weight, position);
		if (position == -1) continue;

		int segPos = find_seg_pos(1, position);

		int unUsedPoint = find_unUsed(segPos);
		if (unUsedPoint == -1) continue;

		
		fixSegTree(unUsedPoint);
		valSum += (long long int )jewels[i].value;
	}
}


int main() {
	scanf("%d %d", &n, &k);
	int a, b;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		jewels[i] = { a, b };
	}

	for (int i = 0; i < k; i++) {
		scanf("%d", bagWeight+i);
	}
	segTree[1].s = 0;
	segTree[1].e = k - 1;

	sort(bagWeight, bagWeight + k);
	sort(jewels, jewels + n, jewelCmp);
	/*
	int val; scanf("%d", &val);
	int valPos = find_pos(0, k - 1, val);
	printf("%d\n", find_pos(0, k - 1, val));
	int segPos = (find_seg_pos(1, valPos));

	printf("%d\n", segPos);
	printf("%d\n", find_seg_pos(1, 1));
	printf("%d\n", find_seg_pos(1, 3));
	printf("%d\n", find_seg_pos(1, 5));
	printf("%d\n", find_seg_pos(1, 7));

	fixSegTree(11);
	printf("%d\n", find_unUsed(segPos));

	fixSegTree(12);
	fixSegTree(13);
	fixSegTree(14);
	fixSegTree(15);

	printf("%d\n", find_unUsed(segPos));
	*/

	pos();
	printf("%lld", valSum);
}