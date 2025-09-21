#define _CRT_SECURE_NO_WARNINGS

/*
	---- 2467_��� ----

	���� ��� �������� ���ؾ� �ϴ� ���� 3���� �Ǵ� ����.
	����ó�� 2���� ���ϴ� ����� ����� �� ����.

	� ����� ����� ���ΰ�?

	1. ������ �� ���� ���� ����.
	2. �� ���� �տ� -1�� ���� ���� ���� ����� ���� index�� ã��.
	
	���⼭ ����� index�� ã�� �� ���� Ž���� �����

	�׷��� �� ���, �ٽ� ������ ��
	: 5000 * 5000 * log5000 ~~ 5000 * 5000 * 15
	�� 3500��ȸ ������ ��. :: 1�� ���� ������ �ذ��� �� ����.

	�� ���� Ž���� �����ϴ� ��찡 ����� ��.
	���� ���� Ž���� �������� : 
	������ ũ�Ⱑ 1�� ���.
	�ش� ���ڸ� ã���� ��� <- �� ������ �����Ե�.

	--> �� ����� ��� ������ ����, �������ͷ� ������.
	-> ������ �ݷʸ� ã�� ����.
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
	arr		:: int* : Ž���� array
	size	:: int	: Ž���� array�� ũ��
	target	:: int	: Ž���� ��
	except1	:: int	: ������ �� 1
	except2	:: int	: ������ �� 2

	:: Action ::

	���� Ž���� ���� �Էµ� target�� ���� ����� ���� ��ġ�� ��ȯ��.
	�������� : 
	1. Ž���ϴ� index�� ���� 1�϶� 
	2. target�� index�� ã���� ��

	�������� ������ index�� ��ȯ��.
	������ ���� ���ؼ� ::
	������ ���� �ش� index�� �����Ǿ��� ���
	1. �ش� index + - 1�߿��� ���̰� ���� ���� index�� ��ȯ��.
	2. 1�� index�� except�� �ش��� ���, �ش� index�� ������ �ٽ� ����.

	���� ��� : ����ġ�� �ξ� ���ϴ� ���¸� �����.

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

		if (val1 <= val2) { // ��������� ���� array�� ���� �� �������
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
	������ ũ�⸦ n��, �ش� ������ nums�� �Է���.
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
