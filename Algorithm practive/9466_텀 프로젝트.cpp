#define _CRT_SECURE_NO_WARNINGS
/*
	9466_ �� ������Ʈ
	���ξ��̵�� 1. �ܼ� �������� ���Ѵ�.

	1. �ϳ��� ����Ŭ�� �ϼ��� ���, �� �ܺο��� �ش� ����Ŭ�� ���� ��� �ڱ� �ڽ����� ���ƿ� �� ����.
	����, ����Ŭ�� ����� ����Ŭ�� ǥ������.

	2. ���� ������ ���� ����
	1. Ž���� �� �� ��.
	2. Ž���� �� ��, ����Ŭ�� �����ϴ� ������ �Ǵܵ�
	3. Ž���� ���� ����.

	3�� ����� ��� �ش� ��ġ�� �������� Ž���� ������.

	�׸��� 3�� ��찡 �������� �� 1�� ��찡 ���� ������ ���� ��쿡 �ش��Ѵ�.

	** ��� �л� ���� �������� ����Ŭ�� ���ϴ� �� �߰��� �� ���� -1�� �ذ�.
	
	���⿡�� �����ؾ� �ϴ� ����
	������ Ž���� ���ΰ�, �̹��� Ž���� ���ΰ�? �ϴ� ���ε�,
	�̸� ���ؼ� ���� 1, 2, 3 case���� '������' �� �����Ѵ�.
	3���� ����̹Ƿ� i��° Ž���� ���, 1�� 3i+1, 2�� 3i+2�� ǥ���Ѵ�.
	Ž���� ���� �������� 0���� �����ȴ�.
*/

#include<stdio.h>

int testCase;
int n, cnt;
int students[100005];
int selects[100005];

void init() {
	cnt = n;
	for (int i = 1; i <= n; i++) students[i] = 0;
}

void checker(int start, int lev) {
	int current = start;
	
	while (students[current] == 0) {
		students[current] = lev * 3 + 1;
		current = selects[current];
	}

	if (students[current] == lev * 3 + 1) {
		while (students[current] == lev * 3 + 1) {
			students[current] = start * 3 + 2;
			current = selects[current];
			cnt--;
		}
	}
	
}


int main() {
	scanf("%d", &testCase);
	for (int i = 0; i < testCase; i++) {
		scanf("%d", &n);
		init();
		int lev = 0;
		for (int q = 1; q <= n; q++) scanf("%d", selects + q);
		for (int q = 1; q <= n; q++) {
			if (students[q] == 0) {
				checker(q, lev); lev++;
			}
		}
		/*
		puts("");
		for (int q = 1; q <= n; q++) {
			printf("%d ", selects[q]);
		}
		puts("");
		for (int q = 1; q <= n; q++) {
			printf("%d ", students[q]);
		}
		puts("\n");
		// for debug
		*/
		printf("%d\n", cnt);
		
	}
}