#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11053_���� �� �����ϴ� �κ� ���� ----

	:: ������ �ִ� ������ 1000���̹Ƿ�, 
	���� �ܼ��� ������ DP�� ����Ѵ�.

	--> �Ʒ� ����� ������ ������.
*/

#include<stdio.h>
#include<queue>
using namespace std;


// ���ݱ��� ������ �κе� �� �ִ� ���̸� �����ϴ� �ڷ���.
typedef struct _number{
	int size;
	int length;
}number;


// 1���� : ����
// 2���� : ���� ũ��(Ŭ���� �ڿ� ��ġ)

struct cmp {
	bool operator()(number a, number b) {
		if (a.length == b.length) {
			return a.size > b.size;
		}
		else return a.length < b.length;
	}

};

priority_queue<number, vector<number>, cmp> prQ;
queue<number> temp;


int nums[1050];


void refill() {
	while (!temp.empty()) {
		prQ.push(temp.front());
		temp.pop();
	}
}



int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}

	for (int i = 0; i < n; i++) {
		refill();

		while (!prQ.empty()) {
			number curr = prQ.top();
			prQ.pop();
			if (curr.size < nums[i]) {
				prQ.push({ nums[i], curr.length + 1 });
				continue;
			}
			temp.push(curr);
			//printf("%d", i);
		}

		prQ.push({ nums[i], 1 });
	}
	refill();

	while (!prQ.empty()) {
		printf("%d %d  //  ", prQ.top().size, prQ.top().length);
		prQ.pop();
	}
	puts("\n");
	printf("%d", prQ.top().length);
}