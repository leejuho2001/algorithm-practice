#define _CRT_SECURE_NO_WARNINGS

/*
	---- 15654_N�� M(5) ----

	�ܼ� ���� ����
	sort ������ ������ ����� ���� �ذ�.
	��� �ٸ� ���ڸ� ������ �����Ƿ�, ��ġ�� ��츸 ����ó���ϸ� ��.

	m������ ������ ������.
	1. �ǳ��ڸ��� ���� +1
	2. �ǳ��ڸ��� ���� m�� �Ѿ�ٸ� �ǳ��ڸ����� 0���� ����� �� ���ڸ��� +1
	3. 2���� �޾ƿø������� ��� �ڸ��� ���� �������� ����

	== �ð��ʰ�
	�� �ð��ʰ��ΰ� ? -> �ð����⵵�� O(n^n)�̱� ����.
	���� 8�ڸ��� ��� 8^8�� �Ǵµ�, �̶����� ������ ���� �ſ� �������� �ȴ�.

	:: �ذ���(��� 2) : backtracking+dynamic programing�� ����Ѵ�.
	Ư�� ������ �������� �ʴ� Ž���� �ƿ� �������� �������ν�
	������ ���� ũ�� ���� �� ����.
	*/
#include<stdio.h>
#include<algorithm>
using namespace std;
/*
int n, m;
int numbers[10];
int address[10];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &numbers[i]);
	sort(numbers, numbers + n);
	for (int i = 0; i < m; i++) address[i] = 0;
	while (address[0] < n) {
		bool flag = false;
		for (int i = 1; i < m; i++) {
			for(int j=0;j<i;j++){ 
				if (address[i] == address[j]) {
					flag = true;
					break;
				}
			}
			if (flag == true) break;
		}
		//�ߺ� ������ üũ

		if (flag == false) {
			for (int i = 0; i < m; i++)printf("%d ", numbers[address[i]]);
			puts("");
		}

		//���ٸ� ���
		address[m - 1] ++;
		for (int q = m - 1; q > 0; q++) {
			if (address[q] < n) break;
			address[q] = 0;
			address[q - 1]++;
		}
	}
}
*/
// ��� 1 (�ð��ʰ�)

int n, m;
int numbers[10];
int address[10];
bool slotDT[10]; // ��� index�� ���ڰ� ���Ǿ��°�? �� Ȯ����.

/*
	---- backTracking ----
	�Է°�
	_index : ���� Ž���� ĭ�� ����
	_level : ������ ������ ���� (level 3: 3�� ������)

	�������� :
	1. _level == m�϶�
	==> address�� ����Ǿ��ִ� ��� ���� �μ��� �� ��Ʈ��ŷ
*/

void backTracking(int _index, int _level) {
	int index = _index;
	int level = _level;

	if (level > 0) {
		slotDT[index] = true;
		address[level] = numbers[index];
	}

	if (level == m) {
		for (int i = 1; i <= m; i++)
			printf("%d ", address[i]);

		puts("");
		
	}

	else {
		for (int slot = 0; slot < n; slot++) {
			if (slotDT[slot] == false) {
				backTracking(slot, level + 1);
			}
		}
	}

	if (level > 0) {
		slotDT[index] = false;
		address[level] = numbers[index];
	} //��Ʈ��ŷ

}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", numbers + i);
	}

	sort(numbers, numbers + n);

	backTracking(-1, 0);
}