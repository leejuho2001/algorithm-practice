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
		maxSize			// 큐 내부에 들어갈 수 있는 최대 element 수(할당된 배열 크기)
		size			// 큐 내부에 있는 element의 수
		elementCount	// 큐 내부의 각 element의 수를 기록하는 배열(사용여부 모름)
		bigQueue		// 최대 우선순위 큐 (최대힙)
		smallQueue		// 최소 우선순위 큐 (최소힙)
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

	입력값 : DPQ의 주소, DPQ의 크기
	출력값 : 없음.

	DPQ에 기본값을 할당해줌.
	조건 : DPQ의 공간은 malloc에 의해 생성되어있어야함.
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

	입력값 : int형 1차원 배열의 주소, 배열의 크기, push할 정수
	출력값 : 없음.
	
	최대힙에 element를 Push함
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

	입력값 : int형 1차원 배열의 주소, 배열의 크기, push할 정수
	출력값 : 없음.

	최소힙에 element를 Push함
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

	입력값 : DPQ의 주소, push할 정수
	출력값 : 없음

	DPO를 구성하는 최대힙과 최소힙에 element를 push함.
*/
void DPQPush(DPQ* p, int element) {
	MAXHeapInsert(p->bigQueue, p->size, element);
	minHeapInsert(p->smallQueue, p->size, element);
	p->size++;
}
/*
	-----MAXHeapPop-----

	입력값 : delete할 최대 힙의 주소
	출력값 : 삭제된 값을 return함.

	최대힙에 저장되어있는 최대값을 없애고 다시 힙의 형태로 수정함.
	없애는 최대값은 함수 결과로 return됨.
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

	입력값 : delete할 최소 힙의 주소
	출력값 : 삭제된 값을 return함.

	최소힙에 저장되어있는 최솟값을 없애고 다시 힙의 형태로 수정함.
	없애는 최솟값은 함수 결과로 return됨.
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

	입력값 : delete할 DPQ의 주소, 최대/소 pop여부를 결정하는 정수(1 or -1)
	출력값 : 삭제된 값을 return함.

	D 1과 같은 명령어를 받았을때 DPQ에서 최대, 최솟값중 하나를 삭제하는 함수.
	삭제된 값은 함수 결과로 return.
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
