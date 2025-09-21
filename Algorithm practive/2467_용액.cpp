#define _CRT_SECURE_NO_WARNINGS

/*
	---- 2467_��� ----

	���� �䱸���� : ���� 0�� ����� �� ã��
	= ������ ���� ����ϸ鼭 ��ȣ�� �ٸ��ų�, �ش� ���̽��� ���� ��� 
	���� ���� �� ������ ������ ���� ��ȣ�� ������ ã���� ��

	== > ������ ũ�⸦ �������� ������ ��, �ν־� ���غ��鼭 ��.
*/


#include<stdio.h>
#include<algorithm>
using namespace std;

int numbers[100005];

int cmp(const void* a, const void* b){ 
	int num1 = *(int*)a;    
	int num2 = *(int*)b;    

	if (abs(num1) < abs(num2))    
		return -1;      

	if (abs(num1) > abs(num2))    
		return 1;      

	return 0;    
}


int main() {
	int n, min=2134567890;
	scanf("%d", &n);
	int element1 = -1, element2 = -1;

	for (int i = 0; i < n; i++) {
		scanf("%d", numbers + i);
	}

	qsort(numbers, n, sizeof(int), cmp);
	//for (int i = 0; i < n; i++) printf("%d ", numbers[i]);
	//puts("");

	for (int i = 0; i < n - 1; i++) {
		int sum = abs(numbers[i] + numbers[i + 1]);
		if (sum < min) {
			min = sum;
			element1 = numbers[i];
			element2 = numbers[i + 1];
		}
	}

	if (element1 > element2) {
		int idx = element2; 
		element2 = element1;
		element1 = idx;
	}

	printf("%d %d", element1, element2);
}