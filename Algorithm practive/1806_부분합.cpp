#define _CRT_SECURE_NO_WARNINGS

/*
	---- �κ��� ----

	�κ����� ���ϴ� ��� :
	��� ���Ҹ� 0�� index���� n������ ���� ������ ����
	[s+1, e] ������ �κ��� : [0,e] - [0,s]

	���⼭ ��� ���Ұ� 0���� ũ�� ������ �κ��� ���ҵ��� ����������
	-> ���� Ž���� ����� �� ����.

	-> ��� ��쿡 ���� ���� Ž���� ������ : N(nlog n) :1000���� �ѱ��� ����.

	���⼭ ���� Ž������ �߰��ؾ� �ϴ� �� : target���� ũ�ų� ���� ù��° ����
	��� �߰��ϴ°�? Ž���ϴ°�?

	:: Ʋ�ȴ� �κ� : 
	�� �κ��� - �� �κ��� = ��ǥ�� �̱� ������,
	ã�ƾ��ϴ� �� �κ��� = ��ǥ�� + �� �κ��� ������,
	��ǥ�� - �� �κ����� ã�� Ʋ��.

	���� 0�� ���(�Ÿ��� 0��)�� ������.
*/
#include<stdio.h>
int n;
int partSum[100050];

int min = 123456789;
int targSum;

int biSearch(int s, int e, int target) {
	if (s == e) { 
		if (partSum[s] >= target) return s;
		else {
			if (s != n && partSum[s + 1] >= target) return s + 1;
			else return -1;
		}
	}
	if (s > e) return -1;
	
	int center = (s + e)/2;
	if (target == partSum[center]) return center;
	else if (target > partSum[center]) return biSearch(center + 1, e, target);
	else return biSearch(s, center - 1, target);
}

int main() {
	scanf("%d %d", &n, &targSum);
	for (int i = 1; i <= n; i++) {
		scanf("%d", partSum + i);
		partSum[i] += partSum[i - 1];
	}

	for (int i = 0; i < n; i++) {
		int target = targSum + partSum[i];

		int res = biSearch(i, n, target);
		if (res != -1) {
			int distance = res - i;
			if (min > distance) { 
				min = distance; 
				//printf("result distance :: %d, - %d ~ %d\n", distance, i, res);
			}
		}
	}

	if (min == 123456789) printf("0");
	else printf("%d", min);
}