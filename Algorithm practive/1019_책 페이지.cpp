#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1019_å ������ ----

	�ְ��ڸ�������, �ϳ��� �������� ��������� ������ �����.
	�ְ������� ���� : 10 ^ �ش� ���� -1 ��ŭ, �ش� ���� -1���� �����ش�.
	�׸��� �ش� ������ ��쿣 �ְ������� ���� ������ + 1 ��ŭ �����ش�.
	
	�׸��� �̸� ��������� �ݺ��Ѵ�.

	--> �̴� 0�� ������� �ʴ� ��쿡 ������ ���.
	1000�� ������ ���, 9���� 009�� ���鼭 �� �������� 0�� ������ �߻��Ѵ�.

	����, �̸� ���ִ� ������ �ʿ��ϴ�.

*/

#include<stdio.h>
long long int nums[10];

long long int pow10(int n) {
	long long int res = 1;
	for (long long int i = 0; i < n; i++) {
		res *= 10;
	}
	return res;
}

void countnum(int target, int len) {
	int temp = target;
	if (target == 0) {
		nums[0] += len;
		return;
	}

	if (len <= 1) {
		for (int i = 0; i <= target; i++) nums[i] ++;
		return;
	}
	int templen = len - 1;;

	long long int piv = (long long int)pow10(templen);

	for (int i = 0; i < target / piv; i++) {
		nums[i] += piv;
		for (int i = 0; i < 10; i++)
			nums[i] += (long long int)templen * piv / 10;
	}
	nums[target / piv] += (long long int)target % piv + 1;

	countnum(target % piv, len -1);
}

int main() {
	int n; scanf("%d", &n);
	int tempp = n; 
	int lenn = 0;
	while (tempp > 0) {
		lenn++;
		tempp /= 10;
	}

	countnum(n, lenn);

	int temp = n, len = 0;
	while (temp > 0) {
		len++;
		temp /= 10;
	}
	for (long long int i = 1; i <= len; i++) {
		if (len - i >= 1) {
		nums[0] -= (long long int)i * (pow10(len - i) * 9 / 10);
		}
		else nums[0] -= i;
	}

	for (int i = 0; i <= 9; i++) printf("%lld ", nums[i]);
}
