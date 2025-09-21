#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2473_세 용액 _ 2P ----

	투 포인터를 이용한 풀이방식
*/


#include<stdio.h>
#include<algorithm>
using namespace std;

int cmp(const void* a, const void* b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;
}

long long int lldabs(long long int lld) {
	if (lld > 0) return lld;
	else return -1 * lld;
}

int main() {
	long long int min = 1234567899999;
	int answers[3] = {};
	int n; scanf("%d", &n);
	int nums[5005] = {};
	for (int i = 0; i < n; i++) scanf("%d", nums + i);
	qsort(nums, n, sizeof(int), cmp);

	for (int q = 0; q < n - 2; q++) {
		int l = q + 1;
		int r = n - 1;

		while (r >= l + 1) {
			long long int sum = (long long int) nums[q] + nums[l] + nums[r];
			if (lldabs(sum) < min) {
				min = lldabs(sum);
				answers[0] = nums[q];
				answers[1] = nums[l];
				answers[2] = nums[r];
			}

			if (lldabs((long long int)nums[q] + nums[l + 1] + nums[r]) > lldabs((long long int)nums[q] + nums[l] + nums[r - 1])) r--;
			else l++;
		}
	}
	qsort(answers, 3, sizeof(int), cmp);
	for (int i = 0; i < 3; i++) {
		printf("%d ", answers[i]);
	}
}