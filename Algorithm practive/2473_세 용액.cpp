#define _CRT_SECURE_NO_WARNINGS

/*
	---- 2467_용액 ----

	기존 용액 문제에서 더해야 하는 값이 3개가 되는 문제.
	이전처럼 2개씩 비교하는 방법을 사용할 수 없음.

	어떤 방식을 사용할 것인가?

	1. 임의의 두 수의 합을 구함.
	2. 두 수의 합에 -1을 곱한 값과 가장 가까운 수의 index를 찾음.
	
	여기서 사용할 index를 찾는 데 이진 탐색을 사용함

	그렇게 될 경우, 핵심 연산의 수
	: 5000 * 5000 * log5000 ~~ 5000 * 5000 * 15
	약 3500만회 정도가 됨. :: 1초 내로 문제를 해결할 수 있음.

	단 이진 탐색은 실패하는 경우가 없어야 함.
	따라서 이진 탐색의 종료조건 : 
	구간의 크기가 1인 경우.
	해당 숫자를 찾았을 경우 <- 두 가지로 나뉘게됨.

	--> 이 방법은 계속 오답이 나와, 투포인터로 구현함.
	-> 적절한 반례를 찾지 못함.
*/
#include<stdio.h>
#include<algorithm>
using namespace std;

long long int minn = 123456789999;
int minarr[3];

int binarySearch(int* arr, int size, int target, int except1, int except2);
int diff(int a, int b);

/*
	---- binarySearch ----
	:: params ::
	arr		:: int* : 탐색할 array
	size	:: int	: 탐색할 array의 크기
	target	:: int	: 탐색할 값
	except1	:: int	: 제외할 값 1
	except2	:: int	: 제외할 값 2

	:: Action ::

	이진 탐색을 통해 입력된 target과 가장 가까운 값의 위치를 반환함.
	종료조건 : 
	1. 탐색하는 index의 수가 1일때 
	2. target의 index를 찾았을 때

	마지막에 결정된 index를 반환함.
	제외할 값에 대해서 ::
	제외할 값이 해당 index로 결정되었을 경우
	1. 해당 index + - 1중에서 차이가 작은 수의 index를 반환함.
	2. 1의 index도 except에 해당할 경우, 해당 index의 옆값과 다시 비교함.

	구현 방법 : 가중치를 두어 더하는 형태를 사용함.

	*/
int binarySearch(int* arr, int sp, int ep, int target, int except1, int except2) {

	int startPoint = sp;
	int endPoint = ep;
	int center = 0;
	int result = 0;

	while (1) {
		//printf("%d %d\n", startPoint, endPoint);
		if (startPoint > endPoint) {
			printf("error :: startPoint is bigger than endPoint\n");
			return -9999;
		}
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

	if (result < sp || result > ep) {
		printf("error:: binarySearch: index out of range %d :: start : %d, end : %d\n", result, sp, ep);
		return -9999999;
	}
	return arr[result];
}
/*
bool isExcept(int a, int ex1, int ex2) {
	return (a == ex1 || a == ex2);
}

int checkDiff(int* arr, int target, int a, int b) {
	int val1 = diff(target, arr[a]);
	int val2 = diff(target, arr[b]);

	if (val1 < val2) return a;
	else return b;
}
*/

int diff(int a, int b) {
	return abs(a - b);
}

/*
	---- input ----
	:: Action ::
	수열의 크기를 n에, 해당 수열을 nums에 입력함.
*/

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
	int n=0;
	int nums[5005] = {};
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", nums + i);
	qsort(nums, n, sizeof(int), cmp);

	for (int i = 0; i < n - 2; i++) {
		for (int q = i + 1; q < n-1; q++) {
			//printf("\n\n------case ::%d %d -------\n\n", i, q);

			int first = nums[i];
			int second = nums[q];
			int third = binarySearch(nums, q+1, n-1, -1 * (first + second), i, q);
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
