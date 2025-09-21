#define _CRT_SECURE_NO_WARNINGS
/*
	---- 1068_트리 ----

	리스트의 배열 형태를 사용하여 트리를 표현.
	입력이 n(0아님) 일 경우 n번째 리스트에 해당 index를 추가함.
	-1이 입력될 경우 별개의 변수 head를 통해 

	입력의 범위가 최대 50임을 이용함. <- 배열을 사용하는 이유.

	0개인걸 어떻게 확인하는가?
	head를 제거할 경우 변수 head를 -1로 전환, 그리고 -1일 경우 리프노드를 0개로 취급.
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