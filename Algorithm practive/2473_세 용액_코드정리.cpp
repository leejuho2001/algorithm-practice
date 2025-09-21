#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<algorithm>
using namespace std;

long long int minn = 123456789999;
int minarr[3];

int binarySearch(int* arr, int size, int target);
int diff(int a, int b);

int binarySearch(int* arr, int sp, int ep, int target) {

	int startPoint = sp;
	int endPoint = ep;
	int center = 0;
	int result = 0;

	while (1) {
		if (startPoint == endPoint) {
			result = startPoint;
			break;
		}



		center = (startPoint + endPoint) / 2;

		int val1 = diff(target, arr[center]);
		int val2 = diff(target, arr[center + 1]);

		if (val1 == 0) {
			result = center;
			break;
		}
		if (val2 == 0) {
			result = center + 1;
			break;
		}

		if (val1 <= val2) { // 상대적으로 왼쪽 array의 차가 더 작은경우
			endPoint = center;
		}
		else {
			startPoint = center + 1;
		}

	}
	return arr[result];
}

int diff(int a, int b) {
	return abs(a - b);
}

int cmp(const void* a, const void* b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;
}

long long int lldabs(long long int a) {
	if (a > 0) return a;
	else return -1 * a;
}

int main() {
	int n = 0;
	int nums[5005] = {};
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", nums + i);
	qsort(nums, n, sizeof(int), cmp);

	for (int i = 0; i < n - 2; i++) {
		for (int q = i + 1; q < n - 1; q++) {
			//printf("\n\n------case ::%d %d -------\n\n", i, q);

			int first = nums[i];
			int second = nums[q];
			int third = binarySearch(nums, q + 1, n - 1, -1 * (first + second));
			//printf("BS result = %d\n", third);

			long long int sum = (long long int) first + second + third;
			if (lldabs(sum) < minn) {
				minn = lldabs(sum);
				minarr[0] = first;
				minarr[1] = second;
				minarr[2] = third;
			}
		}
	}

	qsort(minarr, 3, sizeof(int), cmp);
	printf("%d %d %d", minarr[0], minarr[1], minarr[2]);
}
