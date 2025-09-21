#define _CRT_SECURE_NO_WARNINGS

/*
	---- 부분합 ----

	부분합을 구하는 방법 :
	모든 원소를 0번 index부터 n번까지 더한 값으로 정합
	[s+1, e] 구간의 부분합 : [0,e] - [0,s]

	여기서 모든 원소가 0보다 크기 때문에 부분합 원소들은 오름차순임
	-> 이진 탐색을 사용할 수 있음.

	-> 모든 경우에 대해 이진 탐색을 실행함 : N(nlog n) :1000만을 넘기지 않음.

	여기서 이진 탐색으로 발견해야 하는 것 : target보다 크거나 같은 첫번째 원소
	어떻게 발견하는가? 탐색하는가?

	:: 틀렸던 부분 : 
	앞 부분합 - 뒷 부분합 = 목표값 이기 때문에,
	찾아야하는 앞 부분합 = 목표값 + 뒷 부분합 이지만,
	못표값 - 뒷 부분합을 찾아 틀림.

	합이 0인 경우(거리가 0임)을 배제함.
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