/*
	---- 15663_N��M (9) ----

	���̵�� : 
	�̹� ������ �ٽ��� �� ���ڰ� �� �� �̻� ������ �� �ִٴ� ���̸�,
	���� ���ڳ����� ������ ������ �ʴ´�.
	������, �ߺ��Ǵ� �������� ��� �������־���ϴ� ������ �����̴�.

	�������� �迭�� ���ڸ� �����ϴ� ����� ����ߴµ�, �� ��쿣 �迭�� ���ڰ� �� ���� �� �� �ְ�,
	�׷��� �� ��� ������ �ݴ�� ����� �� �ְԵȴ�.

	����, �̸� �����ϱ� ���� 1���� ���Ҹ� ����� �� �ִ� Ƚ�� �� ���·� �����Ѵ�.

	ex) 9 4 1 9 �� 1, 4, 9 �� ����Ǹ�, ���� 1ȸ, 1ȸ, 2ȸ ����� �� �ִ�.

	�̷��� �� ���, �ϳ��� ���ڰ� �� �� �̻� ������ �ߺ��Ǵ� ������ �߻����� �ʴ´�.
	��� ���°�? �� ������ �Ǳ� �����̴�.

	���� ������ ���� �������� �߻��Ѵ�.

	�����ϴ� �ڷ��� : int �� -> key, quantity ���� ������ struct
	DT�� ���� : DT�� true�ΰ�? -> DT�� ���� quantity������ ū��?

	�׸��� �̿� ���� �������� �ݿ��� Backtracking�� ���� ������ �ذ��Ѵ�.

*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<algorithm>

using namespace std;

typedef struct _number {
	int key;
	int quantity;
}number;

int N, M;
int arraySize;
number numberArr[10];
int address[10];
int DT[10];

bool comp(number a, number b) {
	return a.key < b.key;
}

/*
	---- input ----
	param : ����

	���� : 
	1. int�� ���� temp�� �����Ѵ�.
	2. temp�� ����� ���� numberArr ���� �ִ��� Ȯ���Ѵ�.
	3-1. ������� �ش� �׸��� quantity�� 1 �ø���.
	3-2. numberArr�� ������� arraySize�� 1 �ø���, ��index�� ���ο� ������ �־��ش�.
*/
void input() {
	arraySize = 0;
	for (int _ = 0; _ < N; _++) {
		bool flag = false;
		int temp;
		scanf("%d", &temp);
		for (int i = 0; i < arraySize; i++) {
			if (numberArr[i].key == temp) { 
				numberArr[i].quantity++; 
				flag = true;
				break;
			}
		}
		if (flag == false) {
			numberArr[arraySize] = { temp, 1 };
			arraySize++;
		}
	}
}

/*
	---- backTracking ----
	param
	_index : ���� Ž���� ĭ�� ����
	_level : ������ ������ ���� (level 3: 3�� ������)

	�������� :
	1. _level == m�϶�
	==> address�� ����Ǿ��ִ� ��� ���� �μ��� �� ��Ʈ��ŷ

	������ : DT�� ����� ������ numberArr�� ����� quantity���� ������?
	�� Ž�� ������ ������.
*/

void backTracking(int _index, int _level) {
	int index = _index;
	int level = _level;

	if (level > 0) {
		DT[index]++;
		address[level] = numberArr[index].key;
	}

	if (level == M) {
		for (int i = 1; i <= M; i++)
			printf("%d ", address[i]);

		puts("");

	}

	else {
		for (int slot = 0; slot < arraySize; slot++) {
			if (DT[slot] < numberArr[slot].quantity) {
				backTracking(slot, level + 1);
			}
		}
	}

	if (level > 0) {
		DT[index]--;
		address[level] = 0;
	} //��Ʈ��ŷ

}

int main() {
	scanf("%d %d", &N, &M);

	input();
	sort(numberArr, numberArr + arraySize, comp);

	backTracking(-1, 0);
}



