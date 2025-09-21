#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11689_GCD(n, k) = 1 ----

	n(a^b) : n(a) + n(b) - n(avb)를 이용한다.
	따라서, 소인수 분해를 해주어야 한다.
	소인수 분해를 어떻게 할 것인가?

	남아있는 인수가 소수인지 아닌지 확인하는것이 중요함.
	따라서, 전체적인 베이스는 n까지 탐색하면서, 해당 인수가 소수임이 밝혀지면 중단해야함.
	소수인지 밝히는 방법 : n이 소수인지 판별할 때 , sqrt(n)까지 나눠지지 않을 경우, 소수라고 판명함.

	따라서, 2부터 sqrt(n)까지 탐색하는 부분이 중요함.
	-> 찾은 소인수를 p라고 할 경우, n = p^q * r 형태를 가지게 될 것이다.
	여기서, r에 대해서 재귀적으로 처리한다.
*/

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

typedef struct _factor {
	long long int value;
	long long int level;
}factor;

void prF(list<long long int>& factors, long long int target) {
	long long int prime = 0;
	if (target == 1) return;
	for (long long int i = 2; i * i <= target; i++) {
		if (target % i == 0) {
			prime = i;
			break;
		}
	}

	if (prime == 0) {
		factors.push_back(target);
		return;
	}
	else {
		factors.push_back(prime);
		long long int temp = target;
		while (temp % prime == 0) temp /= prime;
		prF(factors, temp);
	}
}

void extendFactor(list <long long int>& factors, list<factor>& extended) {
	queue<factor> factorQ = {};

	for (list<long long int>::iterator iter = factors.begin(); iter != factors.end(); iter++) {
		long long int curr = *iter;
		for (list<factor>::iterator iter = extended.begin(); iter != extended.end(); iter++) {
			factor current = *iter;
			factorQ.push({ current.value * curr, current.level + 1 });
		}
		factorQ.push({ curr, 1 });

		while (!factorQ.empty()) {
			extended.push_back(factorQ.front());
			factorQ.pop();
		}
	}
}

int main() {
	list<long long int> fs = {};
	list<factor>exfs = {};
	long long int n; scanf("%lld", &n);
	if (n == 1) {
		printf("1"); return 0;
	}

	prF(fs, n);
	extendFactor(fs, exfs);

	/*
	for (list<int>::iterator iter = fs.begin(); iter != fs.end(); iter++)
		printf("%d ", *iter);
	puts("\n");
	for (list<factor>::iterator iter = exfs.begin(); iter != exfs.end(); iter++) {
		printf("%d %d\n", iter->value, iter->level);
	}*/

	long long int base = n;
	long long int sign = 1;
	for (list<factor>::iterator iter = exfs.begin(); iter != exfs.end(); iter++) {		
		if (iter->level % 2 == 0) sign = 1;
		else sign = -1;

		base += (n / iter->value) * sign;
	}

	printf("%lld", base);
}