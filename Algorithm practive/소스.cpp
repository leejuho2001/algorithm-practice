#define _CRT_SECURE_NO_WARNINGS

/*
#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int classification(string s) {
	if (s.compare("(") == 0) return 1;
	else if (s.compare("*") == 0 || s.compare("/") == 0) return 2;
	else if (s.compare("+") == 0 || s.compare("-") == 0) return 3;
	else if (s.compare(")") == 0) return 4;
	else return 5;
}

void get_post(queue<string>* post, queue<string> in) {
	stack<string> st;

	while (!in.empty()) {
		int f_class = classification(in.front());
		if (f_class == 5) (*post).push(in.front());
		else if (f_class == 4) {
			while (classification(st.top()) != 1) {
				post->push(st.top());
				st.pop();
			}
			st.pop();
		}
		else {
			if (st.empty() || classification(st.top()) == 1 || classification(st.top())>f_class) {
				st.push(in.front());
			}
			else if (f_class >= classification(st.top())) {
				while (!st.empty() && f_class >= classification(st.top())) {
					post->push(st.top());
					st.pop();
				}
				st.push(in.front());
			}
			
		}
		in.pop();
	}

	while (!st.empty()) {
		post->push(st.top());
		st.pop();
	}

}



int main() {
	queue<string> in;
	queue<string> in2;
	queue<string>* post = new queue<string>;
	in.push("(");
	in.push("1");
	in.push("+");
	in.push("4");
	in.push(")");
	in.push("*");
	in.push("2");
	in.push("+");
	in.push("8");
	in.push("/");
	in.push("2");
	in2.push("A");
	in2.push("+");
	in2.push("B");
	in2.push("/");
	in2.push("C");
	in2.push("*");
	in2.push("D");
	in2.push("*");
	in2.push("(");
	in2.push("E");
	in2.push("+");
	in2.push("F");
	in2.push(")");
		

	get_post(post, in);
	
	while (!post->empty()) {
		cout << post->front() << " ";
		post->pop();
	}
	cout << endl;
	get_post(post, in2);
	while (!post->empty()) {
		cout << post->front() << " ";
		post->pop();
	}

}*/



#include<stdio.h>
#include<stdlib.h>

void swap(int* arr, int s, int e) {
	int empty = 0;
	empty = arr[s];
	arr[s] = arr[e];
	arr[e] = empty;
}

/*
	 -----DPQ-----
	 
	 DualPriorityQueue

	 param:
		maxSize			// ť ���ο� �� �� �ִ� �ִ� element ��(�Ҵ�� �迭 ũ��)
		size			// ť ���ο� �ִ� element�� ��
		elementCount	// ť ������ �� element�� ���� ����ϴ� �迭(��뿩�� ��)
		bigQueue		// �ִ� �켱���� ť (�ִ���)
		smallQueue		// �ּ� �켱���� ť (�ּ���)
*/

typedef struct DualPriorityQueue {
	int size;
	int maxSize;
	int *elementCount;
	int *bigQueue;
	int *smallQueue;
}DPQ;

/*
	-----DPQInit-----

	�Է°� : DPQ�� �ּ�, DPQ�� ũ��
	��°� : ����.

	DPQ�� �⺻���� �Ҵ�����.
	���� : DPQ�� ������ malloc�� ���� �����Ǿ��־����.
*/
void DPQInit(DPQ *p, int size) {
	p->size = 0;
	p->maxSize = size;
	p->elementCount = (int*)malloc(sizeof(int)*size);
	p->bigQueue = (int*)malloc(sizeof(int) * size);
	p->smallQueue = (int*)malloc(sizeof(int) * size);
	
	for (int i = 0; i < size; i++) {
		*((p->elementCount)+i) = 0;
		*((p->bigQueue)+i) = 0;
		*((p->smallQueue)+i) = 0;
	}
}

/*
	-----MAXHeapInsert-----

	�Է°� : int�� 1���� �迭�� �ּ�, �迭�� ũ��, push�� ����
	��°� : ����.
	
	�ִ����� element�� Push��
*/
void MAXHeapInsert(int* heap, int heapSize, int element) {
	int temp = heapSize + 1;
	heap[temp] = element;

	while (temp > 1 && heap[temp] > heap[temp / 2]) {
		swap(heap, temp, temp / 2);
		temp /= 2;
	}
}


/*
	-----minHeapInsert-----

	�Է°� : int�� 1���� �迭�� �ּ�, �迭�� ũ��, push�� ����
	��°� : ����.

	�ּ����� element�� Push��
*/
void minHeapInsert(int* heap, int heapSize,int element) {
	int temp = heapSize + 1;
	heap[temp] = element;

	while (temp > 1 && heap[temp] < heap[temp / 2]) {
		swap(heap, temp, temp / 2);
		temp /= 2;
	}
}


/*
	-----DPQPush-----

	�Է°� : DPQ�� �ּ�, push�� ����
	��°� : ����

	DPO�� �����ϴ� �ִ����� �ּ����� element�� push��.
*/
void DPQPush(DPQ* p, int element) {
	MAXHeapInsert(p->bigQueue, p->size, element);
	minHeapInsert(p->smallQueue, p->size, element);
	p->size++;
}
/*
	-----MAXHeapPop-----

	�Է°� : delete�� �ִ� ���� �ּ�
	��°� : ������ ���� return��.

	�ִ����� ����Ǿ��ִ� �ִ밪�� ���ְ� �ٽ� ���� ���·� ������.
	���ִ� �ִ밪�� �Լ� ����� return��.
*/
int MAXHeapPop(int* heap, int heapSize) {
	int result = heap[1]; int temp = 1;
	swap(heap, 1, heapSize);
	int next;

	while (temp*2 <= heapSize) {
		if (temp * 2 == heapSize) next = temp * 2;
		else next = heap[temp * 2] > heap[temp * 2 + 1] ? temp * 2 : temp * 2 + 1;

		if (heap[temp] > heap[next]) break;
		swap(heap, temp, next);
		temp = next;
	}

	return result;
}

/*
	-----minHeapPop-----

	�Է°� : delete�� �ּ� ���� �ּ�
	��°� : ������ ���� return��.

	�ּ����� ����Ǿ��ִ� �ּڰ��� ���ְ� �ٽ� ���� ���·� ������.
	���ִ� �ּڰ��� �Լ� ����� return��.
*/
int minHeapPop(int* heap, int heapSize) {
	int result = heap[1]; int temp = 1;
	swap(heap, 1, heapSize);
	int next;

	while (temp * 2 <= heapSize) {
		if (temp * 2 == heapSize) next = temp * 2;
		else next = heap[temp * 2] < heap[temp * 2 + 1] ? temp * 2 : temp * 2 + 1;

		if (heap[temp] < heap[next]) break;
		swap(heap, temp, next);
		temp = next;
	}

	return result;
}

/*
	-----DPQPOP-----

	�Է°� : delete�� DPQ�� �ּ�, �ִ�/�� pop���θ� �����ϴ� ����(1 or -1)
	��°� : ������ ���� return��.

	D 1�� ���� ��ɾ �޾����� DPQ���� �ִ�, �ּڰ��� �ϳ��� �����ϴ� �Լ�.
	������ ���� �Լ� ����� return.
*/
int DPQPOP(DPQ* p, int dir) {
	if (dir > 0) return MAXHeapPop(p->bigQueue, p->size);
	else return minHeapPop(p->smallQueue, p->size);
	p->size--;
}

/*
int main() {
	int n, command;
	scanf("%d", &n);

	DPQ* dpq = (DPQ*)malloc(sizeof(dpq));
	DPQInit(dpq, 10000000);

	for (int i = 0; i < n; i++) {
		scanf("%d", &command);
		for (int q = 0; q < command; q++) {
			char c;
			int d;
			scanf(" %c %d", &c, &d);
			if (c == 'I') {
				DPQPush(dpq, d);
			}
			else if (c == 'D') {
				if (dpq->size == 0) puts("empty");
				else printf("%d\n", DPQPOP(dpq, d));
			}
			else {
				puts("error");
				return -1;
			}
		}
	}
}*/




int paper[135][135];
int color[3];
int n;

bool check(int _startX, int _startY, int _size) {
	int base = paper[_startX][_startY];
	for (int i = _startX; i < _startX + _size; i++) {
		for (int j = _startY; j < _startY + _size; j++) {
			if (base != paper[i][j]) return false;
		}
	}
	return true;
}

void color_paper(int _startX, int _startY, int _size) {
	int sx = _startX;
	int sy = _startY;
	int s = _size;

	if (s==1 || check(sx, sy, s) == true) {
		color[paper[sx][sy]]++;
		return;
	}

	else {
		color_paper(sx, sy, s / 2);
		color_paper(sx+s/2, sy, s / 2);
		color_paper(sx, sy+s/2, s / 2);
		color_paper(sx+s/2, sy+s/2, s / 2);
		return;
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", paper[i] + j);
		}
	}
	color_paper(0, 0, n);

	printf("%d\n%d", color[0], color[1]);
}
