#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1202_보석 도둑 ----

	방법 1. greedy alg

	아이디어 : value가 높은 순서대로 정렬해놓고,
	가장 높은 value를 가진 물건을 담을 수 있는 봉투 중 가장 작은걸 사용할 수 있다.

	--> 그렇게 사용할 경우 무조건 최대가 된다.

	문제 : 이분탐색을 사용해 찾은 주머니가 이미 사용된 경우?
	배열만 사용한 해시테이블의 경우처럼 다음칸으로 미룬다.
	-> 이 과정은 시간복잡도 O(n)을 가지는 과정이기 때문에, 전체 과정이 n^2logn이된다.
	최악의 경우에는 시간초과가 발생할 가능성이 높음.

	해결방안 : 이를 세그먼트 트리로 해결한다.
	따라서 과정은 이렇게 된다.

	1. 이진트리로 들어갈 수 있는 최소크기의 가방을 찾는다.
	2. 그 가방 부터 가장 큰 가방까지의 구간에서 보석이 들어갈 수 있는 가장 작은 가방을 세그먼트 트리를 이용해 찾는다.
	3. 해당 가방에 보석을 집어넣고 정보를 업데이트한다.


	이진트리가 갖는것 : 자식노드가 모두 true값 : true,
	자식노드가 false값이 하나라도 있으면, false.

	리프노드는 해당 가방에 담겨있는지를 의미함.
	따라서 해당 가방에 넣을 경우 해당 리프노드까지 정보를 업데이트함.
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
} // 보석을 담을 수 있는 가장 작은 가방의 위치


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

}// 해당 point(작은 가방의 위치)에 해당하는 segment tree의 index를 반환함.



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
	// point의 조건 : 루트 노드의 주소여야함.
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