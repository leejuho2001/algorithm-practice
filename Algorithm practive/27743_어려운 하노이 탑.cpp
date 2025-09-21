#define _CRT_SECURE_NO_WARNINGS

/*
	---- 27743_어려운 하노이 탑 ----

	아이디어 :

	1. 같은 크기의 판들끼리 순서가 정해진 하노이탑은 하나의 판을 옮길 때, 
	뒤집어 가면서 옮기는 것과 같은 의미를 가진다.

	2. 뒤집어 가면서 하노이 탑을 옮긴다고 했을 때, 정방향으로 완전히 Destination까지 옮기는 데 걸리는 횟수를 구하는 문제이다.
	도착한 당시 정방향이어야 한다 = 모든 판은 짝수번씩 뒤집혀야 한다.

	3.  모든 판을 짝수번씩 뒤집는 하노이탑의 횟수 >> 일반 하노이 탑의 횟수
	because, 적어도 마지막 판을 두 번 옮겨야 하기 때문.

	4. 하지만, n-1번째 판부턴 일반 하노이 탑으로 옮기더라도 무조건 짝수번씩 옮기게 된다. 
	==> 어려운 하노이탑의 횟수를 구하는 데 일반 하노이 탑의 횟수를 이용하면 된다.

	2번 플레이트를 옮기게 되므로, 그 위의 탑은 2회가 아닌 두배, 4회 옮기게 된다.


	5. 이제 블록이 아닌, 크기가 같은 판의 기준으로 봤을 때,
	맨 마지막 판은 두 번 이동할 것을 한 번에 이동할 수 있다. 

	따라서 마지막 크기의 판들을 이동시키는 데 걸리는 횟수는 2m - 1 이다.


	결론 :
	n 층의 하노이 탑을 옮기는 데 걸리는 최소 횟수를 f(n)이라고 두고,
	한 층이 m개의 판으로 구성되어 있으며 n층인 하노이 탑을 옮기는 데 걸리는 최소 횟수를 f'(n,m)이라고 하자.

	이 때, f(n,m) = 4 * m * f(n-1) + 2 * m - 1.

	하지만, 해당 결론으로 일반 하노이 탑의 횟수를 커버할 수 없으므로,
	m = 1일 땐 f(m)을 사용하도록 한다.



	++n, m의 범위가 3 * 10^9이다.
	이는 int의 양의 범위의 1.5배 약간 안되므로, unsigned int로 n, m을 저장한다. 
	*/

/*
	---- power_divided(int a, int b) ----
	입력 : unsigned int a, b
	출력 : a의 b제곱을 1000000007로 나눈 값을 리턴함.

	이는 일반적인 power가 아닌 분할정복을 통한 거듭제곱을 수행하기 위함임.
*/
#include<stdio.h>

unsigned long long int power_divided(unsigned a, unsigned b) {
	if (b == 0) return (unsigned int)1;
	if (b == 1) return a;
	unsigned int half_result = power_divided(a, b / 2);
	unsigned long long int result;
	unsigned long long int temp = (unsigned long long int) half_result;
	

	if (b % 2) { // 홀수라면
		result = (temp * temp * (unsigned long long int) a) % 1000000007;
	}

	else {
		result = (temp * temp ) % 1000000007;
	}

	return result;
}

unsigned int hanoi(unsigned n) {
	return power_divided(2, n) - 1;
}

unsigned long long int hard_hanoi(unsigned int n, unsigned int m) {
	unsigned long long int result = (unsigned long long int) (4 * m * hanoi(n - 1) + 2 * m - 1) % 1000000007;
	return result;
}

int main() {
	unsigned int N, M;

	scanf("%u %u", &N, &M);
	unsigned int result;

	if (M == 1) result = hanoi(N);
	else result = hard_hanoi(N, M);

	printf("%llu", result);
}

// 다만, 지금 코드는 약간씩 값이 달라지고 있어 수정이 필요함