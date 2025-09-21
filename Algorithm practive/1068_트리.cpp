#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1068_Ʈ�� ----

	����Ʈ�� �迭 ���¸� ����Ͽ� Ʈ���� ǥ��.
	�Է��� n(0�ƴ�) �� ��� n��° ����Ʈ�� �ش� index�� �߰���.
	-1�� �Էµ� ��� ������ ���� head�� ���� 

	�Է��� ������ �ִ� 50���� �̿���. <- �迭�� ����ϴ� ����.

	0���ΰ� ��� Ȯ���ϴ°�?
	head�� ������ ��� ���� head�� -1�� ��ȯ, �׸��� -1�� ��� ������带 0���� ���.
*/


#include<stdio.h>
#include<list>

using namespace std;

list<int>tree[51];
int n; int head;
int cnt;
int except;
void countLeaf(int node) {
	//printf("%d %d\n", node, tree[node].size());
	if (tree[node].size() == 0) {
		cnt++;
		return;

	}

	else {
		for (list<int>::iterator iter = tree[node].begin(); iter != tree[node].end(); iter++) {
			if (*iter == except) {
				int realCnt = tree[node].size() - 1;
				if (realCnt == 0) {
					cnt++;
					return;
				}
				
			}
			else {
				countLeaf(*iter);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int _ = 0; _ < n; _++) {
		int temp; scanf("%d", &temp);
		if (temp == -1) head = _;
		else tree[temp].push_back(_);
	}
	scanf("%d", &except);
	if (except == head) head = -1;

	int curr = head;

	if (head == -1) {
		printf("0");
		return 0;
	}
	else {
		countLeaf(head);
	}

	printf("%d", cnt);
}