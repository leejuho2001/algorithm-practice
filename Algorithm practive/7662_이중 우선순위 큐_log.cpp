#define _CRT_SECURE_NO_WARNINGS
/*
	---- 7662_이중 우선순위 큐_log ----

	최대 / 최소를 뺄 때 마다, 반대편에 어떤 수가 빠졌는지 기록하는 log 리스트를 만든다.
	여기서 log는 이중 우선순위 큐를 이루는 우선순위 큐와 같은 cmp 함수를 사용한다.
	이를 통해 pop 내역을 기억하고 어느 한 쪽의 큐에서 pop을 할 때
	log에 존재하는 수와 같은 수가 top이라면 해당 원소를 그냥 pop하고,
	그것이 아니라면 해당 숫자를 return 하는 방식을 사용한다.

*/
#include<stdio.h>
#include<queue>
using namespace std;

struct maxcmp {
	bool operator()(int a, int b) {
		return a < b;
	}
};

struct mincmp {
	bool operator()(int a, int b) {
		return a > b;
	}
};


typedef struct _deprq {
	int size;
	priority_queue<int, vector<int>, maxcmp> maxPrq;
	priority_queue<int, vector<int>, maxcmp> maxLog;

	priority_queue<int, vector<int>, mincmp> minPrq;
	priority_queue<int, vector<int>, mincmp> minLog;
}deprq;


void flush(deprq* q) {
	while (!q->minLog.empty() && q->minLog.top() == q->minPrq.top()) {
		q->minPrq.pop();
		q->minLog.pop();
	}

	while (!q->maxLog.empty() && q->maxLog.top() == q->maxPrq.top()) {
		q->maxPrq.pop();
		q->maxLog.pop();
	}
}

void Push(deprq* q, int value) {
	q->maxPrq.push(value);
	q->minPrq.push(value);
	q->size++;
}

int pop_max(deprq* q) {
	
	flush(q);
	int returnRes = q->maxPrq.top();
	if (q->maxPrq.top() == q->minPrq.top()) q->minPrq.pop();
	else q->minLog.push(returnRes);
	q->maxPrq.pop();
	q->size--;
	return returnRes;
}

int pop_min(deprq* q) {
	flush(q);
	int returnRes = q->minPrq.top();
	if (q->minPrq.top() == q->maxPrq.top()) q->maxPrq.pop();
	else q->maxLog.push(returnRes);
	q->minPrq.pop();
	q->size--;
	return returnRes;
}

int top(deprq* q) {
	return q->maxPrq.top();
}

int bottom(deprq* q) {
	return q->minPrq.top();
}

int main() {
	deprq dpq;
	int n, m;
	char command;
	int command2;
	scanf("%d", &n);
	for (int _ = 0; _ < n; _++) {
		dpq = {};
		scanf("%d", &m);
		for (int __ = 0; __ < m; __++) {
			scanf(" %c", &command);
			if (command == 'I') {
				scanf("%d", &command2);
				Push(&dpq, command2);
			}
			else {
				scanf("%d", &command2);
				if (dpq.size > 0) {
					if (command2 == 1) pop_max(&dpq);
					else pop_min(&dpq);
				}

			}
		}
		flush(&dpq);
		if (dpq.size == 0) printf("EMPTY\n");
		else printf("%d %d\n", top(&dpq),bottom(&dpq));
	}
}