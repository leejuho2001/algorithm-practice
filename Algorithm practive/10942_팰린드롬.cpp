#define _CRT_SECURE_NO_WARNINGS
/*
	---- 10942_�Ӹ���� ----
	�޸������̼��� Ȱ���Ͽ� Ǯ����.
	DT[2002][2002] �� �����Ͽ� ������ ���� �������� ���.
	1	: 1�� ���� �Ӹ����(�Ӹ������ �����ϴ� ��� ���� ���� �Ӹ����)
	2	: 2�� ���� �Ӹ����(�Ӹ������ �����ϴ� ���� ������ 2 ���� �̻��� �Ӹ����)
	0	: ���� Ž������ ����
	-1	: �Ӹ������ �ƴ�.

	�Ӹ���� ��Ģ
	: �Ӹ���� ���� : 
	���� [s, e]�� ���� ��, [s+1, e-1] ������ �Ӹ�����̸�, arr[s] �� arr[e]�� ������ �Ӹ����.
	
	1�� ���� �Ӹ���� ���� : 
	1. �Ӹ�����ϰ�, 
	2. [s+1, e-1] ������ 1�� ���� �Ӹ�����ϰ� 
	3. arr[s] == arr[s+1]�ϰ�.

	2�� ���� �Ӹ���� ���� :	
		�⺻ �Ӹ���� ������ �����Ѵٴ� ���� ������
		1. [s+1, e-1] ������ 1�� ���� �Ӹ������ ���, arr[s] != arr[s+1]�ϰ�
		2. [s+1, e-1]������ 2�� ���� �Ӹ������ ��� �߰� ���� ����.

	1�� ���� �Ӹ������ ����
	-> [s, e]�� �κ����տ� �ش��ϴ� ������ ��� �Ӹ���ҿ� �ش���.

	�Ӹ������ �ƴҰ��
	: [s-n, e+n] (s-n >= 0 && e+n<= N-1) (N�� ������ ����) �� ��� �Ӹ������ �ƴ�.
	�̸� �̿��ؼ� DT�� ä������ ��͸� �̿��� Ž��.

	-> ���� : �� �ٸ� ���� ���� �޸������̼��� ���� ��� �ð��ʰ��� ���̴�.
	�ð��ʰ��� ��������. ����� n^2�� ���� �ʴ� ����.
	���ܰ� �����Ұ����� ���̳�, Ȯ��ġ ����.
	*/

#include<stdio.h>

int n;
int DT[2002][2002];
int arr[2002];

int isPalindrome(int s, int e) {
	if (DT[s][e] != 0) return DT[s][e];

	if (s == e) return DT[s][e] = 1;
	if (e == s + 1) {
		if (arr[s] == arr[e]) return DT[s][e] = true;
		else {
			return DT[s][e] = -1;
		}
	}

	bool condition1 = arr[s] == arr[e];
	bool condition2 = isPalindrome(s + 1, e - 1) > 0;

	// 1�� ����

	if (condition1 && condition2) {
		return DT[s][e] = 1;
	}
	else {
		return DT[s][e] = -1;
	}

	// 2�� ����
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);

	int m; scanf("%d", &m);
	int s, e, res;
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &s, &e);
		res = isPalindrome(s-1, e-1);
		if (res > 0) {
			puts("1");
		}
		else {
			puts("0");
		}
	}
}

/*
#include<stdio.h>

int n;
int DT[2002][2002];
int arr[2002];

int isPalindrome(int s, int e) {
	if (DT[s][e] != 0) return DT[s][e];

	if (s == e) return DT[s][e] = 1;
	if (e == s + 1) {
		if (arr[s] == arr[e]) return DT[s][e] = 1;
		else { 
			extendNotPalindrome(s, e);
			return DT[s][e] = -1; 
		}
	}

	bool condition1 = arr[s] == arr[e];
	int  condition2 = isPalindrome(s + 1, e - 1);
	bool condition3 = arr[s] == arr[s + 1];

	// 1�� ����

	if (condition1 && condition2 == 1 && condition3) {
		return DT[s][e] = 1;
	}

	// 2�� ����
}

void extendNotPalindrome(int s, int e) {
	int w = 1;
	if (s == 0 || e == n - 1) return;
	
	if (DT[s - w][e + w] == 0) {
		while (s - w >= 0 && e + w < n) DT[s - w][e + w] = -1;
	}
	return;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);
}
*/
// �õ� 2. �߰� ������ ���̴� ����̾����� ���� �õ��� AC�� �¾ƹ��� ������ �ߴ���.