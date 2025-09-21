#define _CRT_SECURE_NO_WARNINGS
/*
	---- 7662_���� �켱���� ť ----

	�⺻ ���̵�� : Priority Queue�� ���� ���� �����ȴ�
	�� : ���� �������� ũ�ų�, �۾����� �� ���������� ������ Ʈ��

	����, Priority�� �����ϴ� �ڷ����� �ϳ� ���� �ش� �ڷ������� ������ �����ϰ� ���� Push / pop �ϴ� ������� �����Ѵ�.
	���� Priority Queue �̹Ƿ�, �ּ����� �ִ��� �� �� ����ؾ� �Ѵ�. 
	�ٸ�, �� �������� ������ �Է¹����Ƿ�, ������ ũ�� ��ü�� Priority�� ����Ѵ�.

	�ٽ� ����: �ּ� / �ִ� ������ pop �ϴ� ������ ���� ��, �ݴ� ������ ���Ҹ� ��� �� / �� ������ ����� ���ΰ�?
*/

#include<stdio.h>

int min_heap[1000050];
int MAX_heap[1000050];
// Priority Queue�� �����ϱ� ���� ����� �� ���� ��.
// 0�� ��ġ�� size�� �����ϰ� �������� ���� �����ϴ� �� ����Ѵ�.
// �ϴ� Ȯ�强�� �����ϰ� ������ �����Ѵ�.


/*
	---- swap ----
	�Է� :	int _p1, �ٲٷ��� ������ ��ġ 1
			int _p2, �ٲٷ��� ������ ��ġ 2
			int _arr, ���Ҹ� �ٲ� �迭(���� ��ü)

	���� : �־��� �迭�� �־��� ��ġ�� �� ������ ���� �ٲ��.
*/

void swap(int _p1, int _p2, int* _arr) {
	int place1 = _p1;
	int place2 = _p2;
	int* array = _arr;

	int empty = array[place1];
	*(array + place1) = place2;
	*(array + place2) = empty;
}


/*
	---- min_hPush, MAX_hPush ----
	�Է� : _v, push�� ����

	���� : ���� ��ü�� �Ű������� �ǳ��� ���� �ִ´�.
	�̋� ���� ��Ģ�� �µ��� ���ҵ��� ��ġ�� �����ȴ�.

	���� �ִ� ��� : init address�� size(���� �� ������ �� ����), �׸��� �ش� ���Ҹ� �������� �Ͽ� 
	���� ������ �������� �ʴ°��, �����Ҷ����� swap��
*/

void min_hPush(int _v) {
	int init_address = min_heap[0];
	int value = _v;
	
	for (int address = init_address; address > 0; address /= 2) {
		if (min_heap[address] > min_heap[address / 2]) break;
		swap(address, address / 2, min_heap);
	}
	
	min_heap[0]++;
}

void MAX_hPush(int _v) {
	int init_address = MAX_heap[0];
	int value = _v;

	for (int address = init_address; address > 0; address /= 2) {
		if (MAX_heap[address] > MAX_heap[address / 2]) break;
		swap(address, address / 2, MAX_heap);
	}

	MAX_heap[0]++;
}

/*
	---- push ----
	�Է� : _v, push�� ����

	���� : ���� Priority Queue�� push�ϴ� �Լ�. �ּ����� �ִ����� push�ϴ� ������ ������.
*/
void push(int _v) {
	int value = _v;
	min_hPush(value);
	MAX_hPush(value);
}


void test_function() {
	int size = min_heap[0];
	int pivot = 1, cnt = 0;
	for (int i = 1; i <= size; i++) {
		printf("%d  ", min_heap[i]);

		if (cnt++ >= pivot) {
			puts("");
			cnt = 0;
			pivot *= 2;
		}
	}
}

int main() {
	min_heap[0] = 1;
	MAX_heap[0] = 1;
	for (int i = 0; i <= 5; i++) {
		int index;
		scanf("%d", &index);
		min_hPush(index);

	}
	test_function();
}


