#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1019_책 페이지 ----

	최고자리수부터, 하나씩 내려가며 재귀적으로 갯수를 세어간다.
	최고차수의 숫자 : 10 ^ 해당 차수 -1 만큼, 해당 숫자 -1까지 더해준다.
	그리고 해당 숫자의 경우엔 최고차수로 나눈 나머지 + 1 만큼 더해준다.
	
	그리고 이를 재귀적으로 반복한다.

	--> 이는 0을 취급하지 않는 경우에 가능한 방식.
	1000이 예시일 경우, 9에서 009로 세면서 더 더해지는 0의 개수가 발생한다.

	따라서, 이를 빼주는 과정이 필요하다.

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
