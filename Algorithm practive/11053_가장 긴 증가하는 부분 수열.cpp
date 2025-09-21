#define _CRT_SECURE_NO_WARNINGS
/*
	---- 11053_가장 긴 증가하는 부분 수열 ----

	:: 숫자의 최대 갯수가 1000개이므로, 
	가장 단순한 형태의 DP를 사용한다.

	--> 아래 답안은 오류가 존재함.
*/

#include<stdio.h>
#include<queue>
using namespace std;


// 지금까지 진행한 부분들 중 최대 길이를 저장하는 자료형.
typedef struct _number{
	int size;
	int length;
}number;


// 1순위 : 길이
// 2순위 : 원소 크기(클수록 뒤에 배치)

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