#define _CRT_SECURE_NO_WARNINGS

/*
	---- 10999_���� �� ���ϱ� 2 ----

	�ϳ��� ���� ��ȭ�� ������ ũ�⸦ ���� segment tree�� ��� ���� ��ȭ��
	�����Ͽ� ��� -> �ð��ʰ�
	::-> �ſ� ���� ������ ���� ���� ��ȭ��ų ���, ���� ��� ��忡 ���� Ž���� �����ϱ� ������ ������ ����.

	����, lazy segment tree�� ������־����.

	1. �⺻���� ���ڴ� ������ ����� ���� ��ȭ�� ������ ũ�⸦ ���� ���ϴ� �Ͱ� ������.
	2. ����� ������ ��ȭ��Ű���� �ϴ� ������ ������ ���Ե� ���, ���� �����ϴ� lazy �׸� �����ִ� ����� �����.
	3. ���� �������� ����ؾ� �� ��� lazy�� �ڿ� �������. 
		lazy�� ������ ��ȭ��(delta) ���� ����Ǹ�, lazy�� ������� �� �ش� ����� lazy�� ��尪�� ���Խ��� �� ��, �ڽĳ����� lazy�� ���� lazy�� ���� ���ϴ�
		����� �����.


	���� ������ ũ�Ⱑ 2^63���� ������, ���� ��� �������� �����÷ο찡 �߻��� �� ����.
	���� long long int�� �� ���� �̷���� ����� ���� �ڷ����� �����.
	���� long long int ���� ���� �����ϱ� ������, ���� ����� ������ �ʿ�� ����
*/
#include<stdio.h>
long long int pivot = 1e18;

typedef struct _loong {
	long long int over;
	long long int under;
}loong;

loong numbers[100005];
loong seg_tree[2100000];
loong lazy[2100000];

void lngInit(loong* l, int value) {
	l->over = value / pivot;
	l->under = value % pivot;
}

void lngSum(loong* l, const loong a, const loong b) {
	int carry = 0;
	l->under = (a.under + b.under) % pivot;
	l->over = (a.over + b.over) % pivot + (a.under + b.under) / pivot;
}

void lngDiff(loong* l, const loong a, const loong b) {
	return lngSum(l, a, { -b.over, -b.under });
}

long long int returnLong(const loong l) {
	return l.over * pivot + l.under;
}

void build_segtree(int index, int s, int e) {

	if (s > e) return;

	if (s == e) {
		seg_tree[index] = numbers[s]; return;
	}
	int center = (s + e) / 2;
	build_segtree(index, s, center);
	build_segtree(index, center+1, e);

	lngSum(seg_tree+index, seg_tree[index * 2], seg_tree[index * 2 + 1]);

}

void fix_segtree(int index, int s, int e, int left, int right, loong value) {

	if (s > e || e<left || s>right) return;

	else if (s >= left && e <= right) {
		lazy[index] = value;
		return;
	}



}


int main() {
	
}