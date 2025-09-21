#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11689_GCD(n, k) = 1 ----

	n(a^b) : n(a) + n(b) - n(avb)�� �̿��Ѵ�.
	����, ���μ� ���ظ� ���־�� �Ѵ�.
	���μ� ���ظ� ��� �� ���ΰ�?

	�����ִ� �μ��� �Ҽ����� �ƴ��� Ȯ���ϴ°��� �߿���.
	����, ��ü���� ���̽��� n���� Ž���ϸ鼭, �ش� �μ��� �Ҽ����� �������� �ߴ��ؾ���.
	�Ҽ����� ������ ��� : n�� �Ҽ����� �Ǻ��� �� , sqrt(n)���� �������� ���� ���, �Ҽ���� �Ǹ���.

	����, 2���� sqrt(n)���� Ž���ϴ� �κ��� �߿���.
	-> ã�� ���μ��� p��� �� ���, n = p^q * r ���¸� ������ �� ���̴�.
	���⼭, r�� ���ؼ� ��������� ó���Ѵ�.
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